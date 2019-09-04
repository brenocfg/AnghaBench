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
 char* estrndup (char*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static char *get_http_header_value(char *headers, char *type)
{
	char *pos, *tmp = NULL;
	int typelen, headerslen;

	typelen = strlen(type);
	headerslen = strlen(headers);

	/* header `titles' can be lower case, or any case combination, according
	 * to the various RFC's. */
	pos = headers;
	do {
		/* start of buffer or start of line */
		if (strncasecmp(pos, type, typelen) == 0) {
			char *eol;

			/* match */
			tmp = pos + typelen;
			eol = strchr(tmp, '\n');
			if (eol == NULL) {
				eol = headers + headerslen;
			} else if (eol > tmp && *(eol-1) == '\r') {
				eol--;
			}
			return estrndup(tmp, eol - tmp);
		}

		/* find next line */
		pos = strchr(pos, '\n');
		if (pos) {
			pos++;
		}

	} while (pos);

	return NULL;
}