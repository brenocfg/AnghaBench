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
typedef  int /*<<< orphan*/  RParse ;

/* Variables and functions */
 int /*<<< orphan*/  REPLACE (char*,char*) ; 
 int WSZ ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* r_str_replace (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,char) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 int /*<<< orphan*/  replace (int,char const**,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int parse(RParse *p, const char *data, char *str) {
	int i, len = strlen (data);
	char w0[WSZ];
	char w1[WSZ];
	char w2[WSZ];
	char w3[WSZ];
	char w4[WSZ];
	char w5[WSZ];
	char *buf, *ptr, *optr;

	if (!strcmp (data, "jr ra")) {
		strcpy (str, "return");
		return true;
	}

	// malloc can be slow here :?
	if (!(buf = malloc (len + 1))) {
		return false;
	}
	memcpy (buf, data, len + 1);

	r_str_replace_char (buf, '(', ',');
	r_str_replace_char (buf, ')', ' ');
	r_str_trim (buf);
	if (*buf) {
		w0[0] = '\0';
		w1[0] = '\0';
		w2[0] = '\0';
		w3[0] = '\0';
		w4[0] = '\0';
		ptr = strchr (buf, ' ');
		if (!ptr) {
			ptr = strchr (buf, '\t');
		}
		if (ptr) {
			*ptr = '\0';
			for (++ptr; *ptr == ' '; ptr++) {
				//nothing to see here
			}
			strncpy (w0, buf, WSZ - 1);
			strncpy (w1, ptr, WSZ - 1);

			optr = ptr;
			ptr = strchr (ptr, ',');
			if (ptr) {
				*ptr = '\0';
				for (++ptr; *ptr == ' '; ptr++) {
					//nothing to see here
				}
				strncpy (w1, optr, WSZ - 1);
				strncpy (w2, ptr, WSZ - 1);
				optr = ptr;
				ptr = strchr (ptr, ',');
				if (ptr) {
					*ptr = '\0';
					for (++ptr; *ptr == ' '; ptr++) {
						//nothing to see here
					}
					strncpy (w2, optr, WSZ - 1);
					strncpy (w3, ptr, WSZ - 1);
					optr = ptr;
					// bonus
					ptr = strchr (ptr, ',');
					if (ptr) {
						*ptr = '\0';
						for (++ptr; *ptr == ' '; ptr++) {
							//nothing to see here
						}
						strncpy (w3, optr, WSZ - 1);
						strncpy (w4, ptr, WSZ - 1);
						optr = ptr;
						// bonus
						ptr = strchr (ptr, ',');
						if (ptr) {
							*ptr = '\0';
							for (++ptr; *ptr == ' '; ptr++) {
								//nothing to see here
							}
							strncpy (w4, optr, WSZ - 1);
							strncpy (w5, ptr, WSZ - 1);
						}
					}
				}
			}
		} else {
			strncpy (w0, buf, WSZ - 1);
		}
		{
			const char *wa[] = { w0, w1, w2, w3, w4, w5 };
			int nw = 0;
			for (i = 0; i < 4; i++) {
				if (wa[i][0] != '\0') {
					nw++;
				}
			}
			replace (nw, wa, str);
			{
				char *p = strdup (str);
				p = r_str_replace (p, "+ -", "- ", 0);
				p = r_str_replace (p, " + ]", "]  ", 0);
				//  p = r_str_replace (p, "if (r0 == r0) trap", "trap            ", 0);
#if EXPERIMENTAL_ZERO
				p = r_str_replace (p, "zero", "0", 0);
				if (!memcmp (p, "0 = ", 4)) *p = 0; // nop
#endif
				if (!strcmp (w1, w2)) {
					char a[64], b[64];
#define REPLACE(x,y) do { \
		int snprintf_len1_ = snprintf (a, 64, x, w1, w1); \
		int snprintf_len2_ = snprintf (b, 64, y, w1); \
		if (snprintf_len1_ < 64 && snprintf_len2_ < 64) { \
			p = r_str_replace (p, a, b, 0); \
		} \
	} while (0)

					// TODO: optimize
					REPLACE ("%s = %s +", "%s +=");
					REPLACE ("%s = %s -", "%s -=");
					REPLACE ("%s = %s &", "%s &=");
					REPLACE ("%s = %s |", "%s |=");
					REPLACE ("%s = %s ^", "%s ^=");
					REPLACE ("%s = %s >>", "%s >>=");
					REPLACE ("%s = %s <<", "%s <<=");
				}
				p = r_str_replace (p, ":", "0000", 0);
				strcpy (str, p);
				free (p);
			}
		}
	}
	free (buf);
	return true;
}