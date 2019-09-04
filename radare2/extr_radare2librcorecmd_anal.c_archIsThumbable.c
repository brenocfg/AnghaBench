#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bits; TYPE_1__* cur; } ;
struct TYPE_6__ {TYPE_3__* assembler; } ;
struct TYPE_5__ {scalar_t__ name; } ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
 int strstr (scalar_t__,char*) ; 

__attribute__((used)) static bool archIsThumbable(RCore *core) {
	RAsm *as = core ? core->assembler : NULL;
	if (as && as->cur && as->bits <= 32 && as->cur->name) {
		return strstr (as->cur->name, "arm");
	}
	return false;
}