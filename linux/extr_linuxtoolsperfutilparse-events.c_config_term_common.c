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
struct perf_event_attr {int config; int config1; int config2; int /*<<< orphan*/  branch_sample_type; } ;
struct TYPE_2__ {int num; int /*<<< orphan*/  str; } ;
struct parse_events_term {int type_term; int /*<<< orphan*/  err_term; int /*<<< orphan*/  err_val; TYPE_1__ val; } ;
struct parse_events_error {int /*<<< orphan*/  help; int /*<<< orphan*/  idx; void* str; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PARSE_EVENTS__TERM_TYPE_BRANCH_SAMPLE_TYPE 142 
#define  PARSE_EVENTS__TERM_TYPE_CALLGRAPH 141 
#define  PARSE_EVENTS__TERM_TYPE_CONFIG 140 
#define  PARSE_EVENTS__TERM_TYPE_CONFIG1 139 
#define  PARSE_EVENTS__TERM_TYPE_CONFIG2 138 
#define  PARSE_EVENTS__TERM_TYPE_INHERIT 137 
#define  PARSE_EVENTS__TERM_TYPE_MAX_STACK 136 
#define  PARSE_EVENTS__TERM_TYPE_NAME 135 
#define  PARSE_EVENTS__TERM_TYPE_NOINHERIT 134 
#define  PARSE_EVENTS__TERM_TYPE_NOOVERWRITE 133 
 int /*<<< orphan*/  PARSE_EVENTS__TERM_TYPE_NUM ; 
#define  PARSE_EVENTS__TERM_TYPE_OVERWRITE 132 
#define  PARSE_EVENTS__TERM_TYPE_SAMPLE_FREQ 131 
#define  PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD 130 
#define  PARSE_EVENTS__TERM_TYPE_STACKSIZE 129 
 int /*<<< orphan*/  PARSE_EVENTS__TERM_TYPE_STR ; 
#define  PARSE_EVENTS__TERM_TYPE_TIME 128 
 int /*<<< orphan*/  check_type_val (struct parse_events_term*,struct parse_events_error*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_term_avail (int,struct parse_events_error*) ; 
 int /*<<< orphan*/  parse_branch_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_events_formats_error_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 void* strdup (char*) ; 

__attribute__((used)) static int config_term_common(struct perf_event_attr *attr,
			      struct parse_events_term *term,
			      struct parse_events_error *err)
{
#define CHECK_TYPE_VAL(type)						   \
do {									   \
	if (check_type_val(term, err, PARSE_EVENTS__TERM_TYPE_ ## type)) \
		return -EINVAL;						   \
} while (0)

	switch (term->type_term) {
	case PARSE_EVENTS__TERM_TYPE_CONFIG:
		CHECK_TYPE_VAL(NUM);
		attr->config = term->val.num;
		break;
	case PARSE_EVENTS__TERM_TYPE_CONFIG1:
		CHECK_TYPE_VAL(NUM);
		attr->config1 = term->val.num;
		break;
	case PARSE_EVENTS__TERM_TYPE_CONFIG2:
		CHECK_TYPE_VAL(NUM);
		attr->config2 = term->val.num;
		break;
	case PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD:
		CHECK_TYPE_VAL(NUM);
		break;
	case PARSE_EVENTS__TERM_TYPE_SAMPLE_FREQ:
		CHECK_TYPE_VAL(NUM);
		break;
	case PARSE_EVENTS__TERM_TYPE_BRANCH_SAMPLE_TYPE:
		CHECK_TYPE_VAL(STR);
		if (strcmp(term->val.str, "no") &&
		    parse_branch_str(term->val.str, &attr->branch_sample_type)) {
			err->str = strdup("invalid branch sample type");
			err->idx = term->err_val;
			return -EINVAL;
		}
		break;
	case PARSE_EVENTS__TERM_TYPE_TIME:
		CHECK_TYPE_VAL(NUM);
		if (term->val.num > 1) {
			err->str = strdup("expected 0 or 1");
			err->idx = term->err_val;
			return -EINVAL;
		}
		break;
	case PARSE_EVENTS__TERM_TYPE_CALLGRAPH:
		CHECK_TYPE_VAL(STR);
		break;
	case PARSE_EVENTS__TERM_TYPE_STACKSIZE:
		CHECK_TYPE_VAL(NUM);
		break;
	case PARSE_EVENTS__TERM_TYPE_INHERIT:
		CHECK_TYPE_VAL(NUM);
		break;
	case PARSE_EVENTS__TERM_TYPE_NOINHERIT:
		CHECK_TYPE_VAL(NUM);
		break;
	case PARSE_EVENTS__TERM_TYPE_OVERWRITE:
		CHECK_TYPE_VAL(NUM);
		break;
	case PARSE_EVENTS__TERM_TYPE_NOOVERWRITE:
		CHECK_TYPE_VAL(NUM);
		break;
	case PARSE_EVENTS__TERM_TYPE_NAME:
		CHECK_TYPE_VAL(STR);
		break;
	case PARSE_EVENTS__TERM_TYPE_MAX_STACK:
		CHECK_TYPE_VAL(NUM);
		break;
	default:
		err->str = strdup("unknown term");
		err->idx = term->err_term;
		err->help = parse_events_formats_error_string(NULL);
		return -EINVAL;
	}

	/*
	 * Check term availbility after basic checking so
	 * PARSE_EVENTS__TERM_TYPE_USER can be found and filtered.
	 *
	 * If check availbility at the entry of this function,
	 * user will see "'<sysfs term>' is not usable in 'perf stat'"
	 * if an invalid config term is provided for legacy events
	 * (for example, instructions/badterm/...), which is confusing.
	 */
	if (!config_term_avail(term->type_term, err))
		return -EINVAL;
	return 0;
#undef CHECK_TYPE_VAL
}