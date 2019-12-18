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
typedef  int /*<<< orphan*/  static_terms ;

/* Variables and functions */
 int __PARSE_EVENTS__TERM_TYPE_NR ; 
 scalar_t__ asprintf (char**,char*,char*,...) ; 
 int /*<<< orphan*/  config_terms_list (char*,int) ; 

char *parse_events_formats_error_string(char *additional_terms)
{
	char *str;
	/* "no-overwrite" is the longest name */
	char static_terms[__PARSE_EVENTS__TERM_TYPE_NR *
			  (sizeof("no-overwrite") - 1)];

	config_terms_list(static_terms, sizeof(static_terms));
	/* valid terms */
	if (additional_terms) {
		if (asprintf(&str, "valid terms: %s,%s",
			     additional_terms, static_terms) < 0)
			goto fail;
	} else {
		if (asprintf(&str, "valid terms: %s", static_terms) < 0)
			goto fail;
	}
	return str;

fail:
	return NULL;
}