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
struct TYPE_4__ {int type; int /*<<< orphan*/  val; TYPE_1__* field; } ;
struct tep_filter_arg {TYPE_2__ str; } ;
struct tep_event_filter {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  TEP_FILTER_CMP_MATCH 131 
#define  TEP_FILTER_CMP_NOT_MATCH 130 
#define  TEP_FILTER_CMP_NOT_REGEX 129 
#define  TEP_FILTER_CMP_REGEX 128 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *str_to_str(struct tep_event_filter *filter, struct tep_filter_arg *arg)
{
	char *str = NULL;
	char *op = NULL;

	switch (arg->str.type) {
	case TEP_FILTER_CMP_MATCH:
		op = "==";
		/* fall through */
	case TEP_FILTER_CMP_NOT_MATCH:
		if (!op)
			op = "!=";
		/* fall through */
	case TEP_FILTER_CMP_REGEX:
		if (!op)
			op = "=~";
		/* fall through */
	case TEP_FILTER_CMP_NOT_REGEX:
		if (!op)
			op = "!~";

		asprintf(&str, "%s %s \"%s\"",
			 arg->str.field->name, op, arg->str.val);
		break;

	default:
		/* ?? */
		break;
	}
	return str;
}