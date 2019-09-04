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
typedef  int /*<<< orphan*/  RStrBuf ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,char*) ; 
 char* r_strbuf_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (char*) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *replace_directives_for(char *str, char *token) {
	RStrBuf *sb = r_strbuf_new ("");
	char *p = NULL;
	char *q = str;
	bool changes = false;
	for (;;) {
		if (q) {
			p = strstr (q, token);
		}
		if (p) {
			char *nl = strchr (p, '\n');
			if (nl) {
				*nl ++ = 0;
			}
			char _ = *p;
			*p = 0;
			r_strbuf_append (sb, q);
			*p = _;
			r_strbuf_appendf (sb, "<{%s}>\n", p + 1);
			q = nl;
			changes = true;
		} else {
			if (q) {
				r_strbuf_append (sb, q);
			}
			break;
		}
	}
	if (changes) {
		free (str);
		return r_strbuf_drain (sb);
	}
	r_strbuf_free (sb);
	return str;
}