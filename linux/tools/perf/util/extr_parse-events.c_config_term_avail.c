#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct parse_events_error {int /*<<< orphan*/ * str; } ;

/* Variables and functions */
#define  PARSE_EVENTS__TERM_TYPE_CONFIG 133 
#define  PARSE_EVENTS__TERM_TYPE_CONFIG1 132 
#define  PARSE_EVENTS__TERM_TYPE_CONFIG2 131 
#define  PARSE_EVENTS__TERM_TYPE_NAME 130 
#define  PARSE_EVENTS__TERM_TYPE_PERCORE 129 
#define  PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD 128 
 int __PARSE_EVENTS__TERM_TYPE_NR ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * config_term_names ; 
 int /*<<< orphan*/  config_term_shrinked ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static bool
config_term_avail(int term_type, struct parse_events_error *err)
{
	if (term_type < 0 || term_type >= __PARSE_EVENTS__TERM_TYPE_NR) {
		err->str = strdup("Invalid term_type");
		return false;
	}
	if (!config_term_shrinked)
		return true;

	switch (term_type) {
	case PARSE_EVENTS__TERM_TYPE_CONFIG:
	case PARSE_EVENTS__TERM_TYPE_CONFIG1:
	case PARSE_EVENTS__TERM_TYPE_CONFIG2:
	case PARSE_EVENTS__TERM_TYPE_NAME:
	case PARSE_EVENTS__TERM_TYPE_SAMPLE_PERIOD:
	case PARSE_EVENTS__TERM_TYPE_PERCORE:
		return true;
	default:
		if (!err)
			return false;

		/* term_type is validated so indexing is safe */
		if (asprintf(&err->str, "'%s' is not usable in 'perf stat'",
			     config_term_names[term_type]) < 0)
			err->str = NULL;
		return false;
	}
}