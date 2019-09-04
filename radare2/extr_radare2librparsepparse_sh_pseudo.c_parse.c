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
 int WSZ ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 int /*<<< orphan*/  replace (int,char const**,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int parse(RParse *p, const char *data, char *str) {
	int i, len = strlen (data);
	char w0[WSZ];
	char w1[WSZ];
	char w2[WSZ];
	char w3[WSZ];
	char w4[WSZ];
	char *buf, *ptr, *optr, *par;

	// malloc can be slow here :?
	if (!(buf = malloc (len + 1))) {
		return false;
	}
	memcpy (buf, data, len + 1);

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
			par = strchr (ptr, '(');
			if (par && strchr (ptr, ',') > par) {
				ptr = strchr (ptr, ')');
				if (ptr) {
					ptr = strchr (ptr, ',');
				}
			} else {
				ptr = strchr (ptr, ',');
			}
			if (ptr) {
				*ptr = '\0';
				for (++ptr; *ptr == ' '; ptr++) {
					//nothing to see here
				}
				strncpy (w1, optr, WSZ - 1);
				strncpy (w2, ptr, WSZ - 1);
				optr = ptr;
				par = strchr (ptr, '(');
				if (par && strchr (ptr, ',') > par) {
					ptr = strchr (ptr, ')');
					if (ptr) {
						ptr = strchr (ptr, ',');
					}
				} else {
					ptr = strchr (ptr, ',');
				}
				if (ptr) {
					*ptr = '\0';
					for (++ptr; *ptr == ' '; ptr++) {
						//nothing to see here
					}
					strncpy (w2, optr, WSZ - 1);
					strncpy (w3, ptr, WSZ - 1);
					optr = ptr;
					// bonus
					par = strchr (ptr, '(');
					if (par && strchr (ptr, ',') > par) {
						ptr = strchr (ptr, ')');
						if (ptr) {
							ptr = strchr (ptr, ',');
						}
					} else {
						ptr = strchr (ptr, ',');
					}
					if (ptr) {
						*ptr = '\0';
						for (++ptr; *ptr == ' '; ptr++) {
							//nothing to see here
						}
						strncpy (w3, optr, WSZ - 1);
						strncpy (w4, ptr, WSZ - 1);
					}
				}
			}
		} else {
			strncpy (w0, buf, WSZ - 1);
		}
		{
			const char *wa[] = { w0, w1, w2, w3, w4 };
			int nw = 0;
			for (i = 0; i < 5; i++) {
				if (wa[i][0] != '\0') {
					nw++;
				}
			}
			replace (nw, wa, str);
		}
	}
	free (buf);
	return true;
}