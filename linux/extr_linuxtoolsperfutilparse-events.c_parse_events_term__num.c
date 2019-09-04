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
typedef  int /*<<< orphan*/  u64 ;
struct parse_events_term {int type_term; char* config; int no_value; int /*<<< orphan*/  err_val; int /*<<< orphan*/  err_term; int /*<<< orphan*/  type_val; } ;
struct TYPE_2__ {int /*<<< orphan*/  first_column; } ;
typedef  TYPE_1__ YYLTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_EVENTS__TERM_TYPE_NUM ; 
 int new_term (struct parse_events_term**,struct parse_events_term*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int parse_events_term__num(struct parse_events_term **term,
			   int type_term, char *config, u64 num,
			   bool no_value,
			   void *loc_term_, void *loc_val_)
{
	YYLTYPE *loc_term = loc_term_;
	YYLTYPE *loc_val = loc_val_;

	struct parse_events_term temp = {
		.type_val  = PARSE_EVENTS__TERM_TYPE_NUM,
		.type_term = type_term,
		.config    = config,
		.no_value  = no_value,
		.err_term  = loc_term ? loc_term->first_column : 0,
		.err_val   = loc_val  ? loc_val->first_column  : 0,
	};

	return new_term(term, &temp, NULL, num);
}