#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* field; } ;
struct tep_filter_arg {TYPE_2__ field; } ;
struct tep_event_filter {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *field_to_str(struct tep_event_filter *filter, struct tep_filter_arg *arg)
{
	return strdup(arg->field.field->name);
}