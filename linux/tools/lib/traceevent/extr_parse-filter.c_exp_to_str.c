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
struct TYPE_2__ {int type; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct tep_filter_arg {TYPE_1__ exp; } ;
struct tep_event_filter {int dummy; } ;

/* Variables and functions */
#define  TEP_FILTER_EXP_ADD 137 
#define  TEP_FILTER_EXP_AND 136 
#define  TEP_FILTER_EXP_DIV 135 
#define  TEP_FILTER_EXP_LSHIFT 134 
#define  TEP_FILTER_EXP_MOD 133 
#define  TEP_FILTER_EXP_MUL 132 
#define  TEP_FILTER_EXP_OR 131 
#define  TEP_FILTER_EXP_RSHIFT 130 
#define  TEP_FILTER_EXP_SUB 129 
#define  TEP_FILTER_EXP_XOR 128 
 char* arg_to_str (struct tep_event_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static char *exp_to_str(struct tep_event_filter *filter, struct tep_filter_arg *arg)
{
	char *lstr;
	char *rstr;
	char *op;
	char *str = NULL;

	lstr = arg_to_str(filter, arg->exp.left);
	rstr = arg_to_str(filter, arg->exp.right);
	if (!lstr || !rstr)
		goto out;

	switch (arg->exp.type) {
	case TEP_FILTER_EXP_ADD:
		op = "+";
		break;
	case TEP_FILTER_EXP_SUB:
		op = "-";
		break;
	case TEP_FILTER_EXP_MUL:
		op = "*";
		break;
	case TEP_FILTER_EXP_DIV:
		op = "/";
		break;
	case TEP_FILTER_EXP_MOD:
		op = "%";
		break;
	case TEP_FILTER_EXP_RSHIFT:
		op = ">>";
		break;
	case TEP_FILTER_EXP_LSHIFT:
		op = "<<";
		break;
	case TEP_FILTER_EXP_AND:
		op = "&";
		break;
	case TEP_FILTER_EXP_OR:
		op = "|";
		break;
	case TEP_FILTER_EXP_XOR:
		op = "^";
		break;
	default:
		op = "[ERROR IN EXPRESSION TYPE]";
		break;
	}

	asprintf(&str, "%s %s %s", lstr, op, rstr);
out:
	free(lstr);
	free(rstr);

	return str;
}