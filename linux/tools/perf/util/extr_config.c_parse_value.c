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
typedef  int /*<<< orphan*/  value ;

/* Variables and functions */
 int get_next_char () ; 
 scalar_t__ isspace (int) ; 

__attribute__((used)) static char *parse_value(void)
{
	static char value[1024];
	int quote = 0, comment = 0, space = 0;
	size_t len = 0;

	for (;;) {
		int c = get_next_char();

		if (len >= sizeof(value) - 1)
			return NULL;
		if (c == '\n') {
			if (quote)
				return NULL;
			value[len] = 0;
			return value;
		}
		if (comment)
			continue;
		if (isspace(c) && !quote) {
			space = 1;
			continue;
		}
		if (!quote) {
			if (c == ';' || c == '#') {
				comment = 1;
				continue;
			}
		}
		if (space) {
			if (len)
				value[len++] = ' ';
			space = 0;
		}
		if (c == '\\') {
			c = get_next_char();
			switch (c) {
			case '\n':
				continue;
			case 't':
				c = '\t';
				break;
			case 'b':
				c = '\b';
				break;
			case 'n':
				c = '\n';
				break;
			/* Some characters escape as themselves */
			case '\\': case '"':
				break;
			/* Reject unknown escape sequences */
			default:
				return NULL;
			}
			value[len++] = c;
			continue;
		}
		if (c == '"') {
			quote = 1-quote;
			continue;
		}
		value[len++] = c;
	}
}