#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_6__* stack; } ;
struct config_string {char** variable; char* reset_val; char* boot_val; TYPE_5__ gen; } ;
struct TYPE_9__ {char* stringval; } ;
struct TYPE_10__ {TYPE_3__ val; } ;
struct TYPE_7__ {char* stringval; } ;
struct TYPE_8__ {TYPE_1__ val; } ;
struct TYPE_12__ {TYPE_4__ masked; TYPE_2__ prior; struct TYPE_12__* prev; } ;
typedef  TYPE_6__ GucStack ;

/* Variables and functions */

__attribute__((used)) static bool
string_field_used(struct config_string *conf, char *strval)
{
	GucStack   *stack;

	if (strval == *(conf->variable) ||
		strval == conf->reset_val ||
		strval == conf->boot_val)
		return true;
	for (stack = conf->gen.stack; stack; stack = stack->prev)
	{
		if (strval == stack->prior.val.stringval ||
			strval == stack->masked.val.stringval)
			return true;
	}
	return false;
}