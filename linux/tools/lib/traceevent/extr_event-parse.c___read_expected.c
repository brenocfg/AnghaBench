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
typedef  enum tep_event_type { ____Placeholder_tep_event_type } tep_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  free_token (char*) ; 
 int read_token (char**) ; 
 int read_token_item (char**) ; 
 int test_type_token (int,char*,int,char const*) ; 

__attribute__((used)) static int __read_expected(enum tep_event_type expect, const char *str,
			   int newline_ok)
{
	enum tep_event_type type;
	char *token;
	int ret;

	if (newline_ok)
		type = read_token(&token);
	else
		type = read_token_item(&token);

	ret = test_type_token(type, token, expect, str);

	free_token(token);

	return ret;
}