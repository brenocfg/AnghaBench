#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tep_format_field {int dummy; } ;
struct TYPE_6__ {struct tep_format_field* field; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; int /*<<< orphan*/  type; int /*<<< orphan*/  str; } ;
struct tep_filter_arg {TYPE_3__ field; void* type; TYPE_2__ boolean; TYPE_1__ value; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_event_type { ____Placeholder_tep_event_type } tep_event_type ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int /*<<< orphan*/  COMM ; 
 int /*<<< orphan*/  CPU ; 
 int TEP_ERRNO__MEM_ALLOC_FAILED ; 
 int TEP_ERRNO__UNEXPECTED_TYPE ; 
#define  TEP_EVENT_DQUOTE 130 
#define  TEP_EVENT_ITEM 129 
#define  TEP_EVENT_SQUOTE 128 
 void* TEP_FILTER_ARG_BOOLEAN ; 
 void* TEP_FILTER_ARG_FIELD ; 
 void* TEP_FILTER_ARG_VALUE ; 
 int /*<<< orphan*/  TEP_FILTER_CHAR ; 
 int /*<<< orphan*/  TEP_FILTER_FALSE ; 
 int /*<<< orphan*/  TEP_FILTER_NUMBER ; 
 int /*<<< orphan*/  TEP_FILTER_STRING ; 
 struct tep_filter_arg* allocate_arg () ; 
 struct tep_format_field comm ; 
 struct tep_format_field cpu ; 
 int /*<<< orphan*/  free_arg (struct tep_filter_arg*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  show_error (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  strtoull (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tep_format_field* tep_find_any_field (struct tep_event*,char const*) ; 

__attribute__((used)) static enum tep_errno
create_arg_item(struct tep_event *event, const char *token,
		enum tep_event_type type, struct tep_filter_arg **parg, char *error_str)
{
	struct tep_format_field *field;
	struct tep_filter_arg *arg;

	arg = allocate_arg();
	if (arg == NULL) {
		show_error(error_str, "failed to allocate filter arg");
		return TEP_ERRNO__MEM_ALLOC_FAILED;
	}

	switch (type) {

	case TEP_EVENT_SQUOTE:
	case TEP_EVENT_DQUOTE:
		arg->type = TEP_FILTER_ARG_VALUE;
		arg->value.type =
			type == TEP_EVENT_DQUOTE ? TEP_FILTER_STRING : TEP_FILTER_CHAR;
		arg->value.str = strdup(token);
		if (!arg->value.str) {
			free_arg(arg);
			show_error(error_str, "failed to allocate string filter arg");
			return TEP_ERRNO__MEM_ALLOC_FAILED;
		}
		break;
	case TEP_EVENT_ITEM:
		/* if it is a number, then convert it */
		if (isdigit(token[0])) {
			arg->type = TEP_FILTER_ARG_VALUE;
			arg->value.type = TEP_FILTER_NUMBER;
			arg->value.val = strtoull(token, NULL, 0);
			break;
		}
		/* Consider this a field */
		field = tep_find_any_field(event, token);
		if (!field) {
			/* If token is 'COMM' or 'CPU' then it is special */
			if (strcmp(token, COMM) == 0) {
				field = &comm;
			} else if (strcmp(token, CPU) == 0) {
				field = &cpu;
			} else {
				/* not a field, Make it false */
				arg->type = TEP_FILTER_ARG_BOOLEAN;
				arg->boolean.value = TEP_FILTER_FALSE;
				break;
			}
		}
		arg->type = TEP_FILTER_ARG_FIELD;
		arg->field.field = field;
		break;
	default:
		free_arg(arg);
		show_error(error_str, "expected a value but found %s", token);
		return TEP_ERRNO__UNEXPECTED_TYPE;
	}
	*parg = arg;
	return 0;
}