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
struct tep_record {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  reg; int /*<<< orphan*/  val; int /*<<< orphan*/ * field; } ;
struct filter_arg {TYPE_1__ str; } ;
struct event_format {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
#define  FILTER_CMP_MATCH 131 
#define  FILTER_CMP_NOT_MATCH 130 
#define  FILTER_CMP_NOT_REGEX 129 
#define  FILTER_CMP_REGEX 128 
 int TEP_ERRNO__ILLEGAL_STRING_CMP ; 
 int /*<<< orphan*/  comm ; 
 char* get_comm (struct event_format*,struct tep_record*) ; 
 char* get_field_str (struct filter_arg*,struct tep_record*) ; 
 int regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_str(struct event_format *event, struct filter_arg *arg,
		    struct tep_record *record, enum tep_errno *err)
{
	const char *val;

	if (arg->str.field == &comm)
		val = get_comm(event, record);
	else
		val = get_field_str(arg, record);

	switch (arg->str.type) {
	case FILTER_CMP_MATCH:
		return strcmp(val, arg->str.val) == 0;

	case FILTER_CMP_NOT_MATCH:
		return strcmp(val, arg->str.val) != 0;

	case FILTER_CMP_REGEX:
		/* Returns zero on match */
		return !regexec(&arg->str.reg, val, 0, NULL, 0);

	case FILTER_CMP_NOT_REGEX:
		return regexec(&arg->str.reg, val, 0, NULL, 0);

	default:
		if (!*err)
			*err = TEP_ERRNO__ILLEGAL_STRING_CMP;
		return 0;
	}
}