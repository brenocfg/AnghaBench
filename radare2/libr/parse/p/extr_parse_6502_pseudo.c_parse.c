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
typedef  int /*<<< orphan*/  w2 ;
typedef  int /*<<< orphan*/  w1 ;
typedef  int /*<<< orphan*/  w0 ;
typedef  int /*<<< orphan*/  RParse ;
typedef  int /*<<< orphan*/  ADDR_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  addr_type (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,char) ; 
 int /*<<< orphan*/  replace (int,char const**,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int parse(RParse *p, const char *data, char *str) {
	char w0[256], w1[256], w2[256];
	int i, len = strlen (data);
	char *buf, *ptr, *optr;
	ADDR_TYPE atype;

	if (len >= sizeof (w0)) {
		return false;
	}
	// malloc can be slow here :?
	if (!(buf = malloc (len + 1))) {
		return false;
	}
	memcpy (buf, data, len + 1);

	if (*buf) {
		atype = addr_type (buf);
		r_str_replace_char (buf, '(', ' ');
		r_str_replace_char (buf, ')', ' ');
		*w0 = *w1 = *w2 = '\0';
		ptr = strchr (buf, ' ');
		if (!ptr) {
			ptr = strchr (buf, '\t');
		}
		if (ptr) {
			*ptr = '\0';
			for (++ptr; *ptr == ' '; ptr++) {
				;
			}
			strncpy (w0, buf, sizeof(w0) - 1);
			strncpy (w1, ptr, sizeof(w1) - 1);
			optr = ptr;
			ptr = strchr (ptr, ',');
			if (ptr) {
				*ptr = '\0';
				for (++ptr; *ptr == ' '; ptr++) {
					;
				}
				strncpy (w1, optr, sizeof(w1) - 1);
				strncpy (w2, ptr, sizeof(w2) - 1);
			}
		} else {
			strncpy (w0, buf, sizeof(w0) - 1);
		}

		const char *wa[] = {w0, w1, w2};
		int nw = 0;
		for (i = 0; i < 3; i++) {
			if (wa[i][0]) {
				nw++;
			}
		}
		replace (nw, wa, str, atype);
	}

	free (buf);

	return true;
}