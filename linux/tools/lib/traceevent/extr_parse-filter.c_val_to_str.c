#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct tep_filter_arg {TYPE_1__ value; } ;
struct tep_event_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *val_to_str(struct tep_event_filter *filter, struct tep_filter_arg *arg)
{
	char *str = NULL;

	asprintf(&str, "%lld", arg->value.val);

	return str;
}