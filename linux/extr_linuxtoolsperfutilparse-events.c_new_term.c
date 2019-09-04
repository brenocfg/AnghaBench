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
struct TYPE_2__ {char* str; int /*<<< orphan*/  num; } ;
struct parse_events_term {int weak; int type_val; TYPE_1__ val; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  PARSE_EVENTS__TERM_TYPE_NUM 129 
#define  PARSE_EVENTS__TERM_TYPE_STR 128 
 int /*<<< orphan*/  free (struct parse_events_term*) ; 
 struct parse_events_term* malloc (int) ; 

__attribute__((used)) static int new_term(struct parse_events_term **_term,
		    struct parse_events_term *temp,
		    char *str, u64 num)
{
	struct parse_events_term *term;

	term = malloc(sizeof(*term));
	if (!term)
		return -ENOMEM;

	*term = *temp;
	INIT_LIST_HEAD(&term->list);
	term->weak = false;

	switch (term->type_val) {
	case PARSE_EVENTS__TERM_TYPE_NUM:
		term->val.num = num;
		break;
	case PARSE_EVENTS__TERM_TYPE_STR:
		term->val.str = str;
		break;
	default:
		free(term);
		return -EINVAL;
	}

	*_term = term;
	return 0;
}