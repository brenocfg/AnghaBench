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

/* Variables and functions */
 char* expand_dollar_with_args (char const**,int,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,size_t) ; 
 char* xmalloc (int) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static char *__expand_string(const char **str, bool (*is_end)(char c),
			     int argc, char *argv[])
{
	const char *in, *p;
	char *expansion, *out;
	size_t in_len, out_len;

	out = xmalloc(1);
	*out = 0;
	out_len = 1;

	p = in = *str;

	while (1) {
		if (*p == '$') {
			in_len = p - in;
			p++;
			expansion = expand_dollar_with_args(&p, argc, argv);
			out_len += in_len + strlen(expansion);
			out = xrealloc(out, out_len);
			strncat(out, in, in_len);
			strcat(out, expansion);
			free(expansion);
			in = p;
			continue;
		}

		if (is_end(*p))
			break;

		p++;
	}

	in_len = p - in;
	out_len += in_len;
	out = xrealloc(out, out_len);
	strncat(out, in, in_len);

	/* Advance 'str' to the end character */
	*str = p;

	return out;
}