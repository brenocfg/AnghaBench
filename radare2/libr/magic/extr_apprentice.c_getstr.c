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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RMagic ;

/* Variables and functions */
 int FILE_COMPILE ; 
 int /*<<< orphan*/  file_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  file_magwarn (int /*<<< orphan*/ *,char*,...) ; 
 int hextoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isprint (int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char * getstr(RMagic *ms, const char *s, char *p, int plen, int *slen, int action) {
	const char *origs = s;
	char *origp = p;
	char *pmax = p + plen - 1;
	int c, val;

	while ((c = *s++) != '\0') {
		if (isspace ((ut8)c)) {
			break;
		}
		if (p >= pmax) {
			file_error(ms, 0, "string too long: `%s'", origs);
			return NULL;
		}
		if (c == '\\') {
			switch ((c = *s++)) {
			case '\0':
				if (action == FILE_COMPILE) {
					file_magwarn (ms, "incomplete escape");
				}
				goto out;
			case '\t':
				if (action == FILE_COMPILE) {
					file_magwarn(ms,
					    "escaped tab found, use \\t instead");
					action++;
				}
				/*FALLTHROUGH*/
			default:
				if (action == FILE_COMPILE) {
					if (isprint ((ut8)c)) {
						file_magwarn (ms,
							"no need to escape `%c'", c);
					} else {
						file_magwarn (ms,
							"unknown escape sequence: \\%03o", c);
					}
				}
				/*FALLTHROUGH*/
			/* space, perhaps force people to use \040? */
			case ' ':
#if 0
			/*
			 * Other things people escape, but shouldn't need to,
			 * so we disallow them
			 */
			case '\'':
			case '"':
			case '?':
#endif
			/* Relations */
			case '>':
			case '<':
			case '&':
			case '^':
			case '=':
			case '!':
			/* and baskslash itself */
			case '\\':
				*p++ = (char) c;
				break;
			case 'a': *p++ = '\a'; break;
			case 'b': *p++ = '\b'; break;
			case 'f': *p++ = '\f'; break;
			case 'n': *p++ = '\n'; break;
			case 'r': *p++ = '\r'; break;
			case 't': *p++ = '\t'; break;
			case 'v': *p++ = '\v'; break;
			/* \ and up to 3 octal digits */
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
				val = c - '0';
				c = *s++;  /* try for 2 */
				if (c >= '0' && c <= '7') {
					val = (val << 3) | (c - '0');
					c = *s++;  /* try for 3 */
					if (c >= '0' && c <= '7') {
						val = (val << 3) | (c-'0');
					} else {
						--s;
					}
				} else {
					--s;
				}
				*p++ = (char)val;
				break;

			/* \x and up to 2 hex digits */
			case 'x':
				val = 'x';	/* Default if no digits */
				c = hextoint(*s++);	/* Get next char */
				if (c >= 0) {
					val = c;
					c = hextoint(*s++);
					if (c >= 0) {
						val = (val << 4) + c;
					} else {
						--s;
					}
				} else {
					--s;
				}
				*p++ = (char)val;
				break;
			}
		} else {
			*p++ = (char)c;
		}
	}
out:
	*p = '\0';
	*slen = p - origp;
	return s;
}