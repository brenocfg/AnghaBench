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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* pestrndup (char const*,size_t,int) ; 
 int php_raw_url_decode (char*,int) ; 

__attribute__((used)) static void normalize_vpath(char **retval, size_t *retval_len, const char *vpath, size_t vpath_len, int persistent) /* {{{ */
{
	char *decoded_vpath = NULL;
	char *decoded_vpath_end;
	char *p;

	*retval = NULL;
	*retval_len = 0;

	decoded_vpath = pestrndup(vpath, vpath_len, persistent);
	if (!decoded_vpath) {
		return;
	}

	decoded_vpath_end = decoded_vpath + php_raw_url_decode(decoded_vpath, (int)vpath_len);

#ifdef PHP_WIN32
	{
		char *p = decoded_vpath;

		do {
			if (*p == '\\') {
				*p = '/';
			}
		} while (*p++);
	}
#endif

	p = decoded_vpath;

	if (p < decoded_vpath_end && *p == '/') {
		char *n = p;
		while (n < decoded_vpath_end && *n == '/') n++;
		memmove(++p, n, decoded_vpath_end - n);
		decoded_vpath_end -= n - p;
	}

	while (p < decoded_vpath_end) {
		char *n = p;
		while (n < decoded_vpath_end && *n != '/') n++;
		if (n - p == 2 && p[0] == '.' && p[1] == '.') {
			if (p > decoded_vpath) {
				--p;
				for (;;) {
					if (p == decoded_vpath) {
						if (*p == '/') {
							p++;
						}
						break;
					}
					if (*(--p) == '/') {
						p++;
						break;
					}
				}
			}
			while (n < decoded_vpath_end && *n == '/') n++;
			memmove(p, n, decoded_vpath_end - n);
			decoded_vpath_end -= n - p;
		} else if (n - p == 1 && p[0] == '.') {
			while (n < decoded_vpath_end && *n == '/') n++;
			memmove(p, n, decoded_vpath_end - n);
			decoded_vpath_end -= n - p;
		} else {
			if (n < decoded_vpath_end) {
				char *nn = n;
				while (nn < decoded_vpath_end && *nn == '/') nn++;
				p = n + 1;
				memmove(p, nn, decoded_vpath_end - nn);
				decoded_vpath_end -= nn - p;
			} else {
				p = n;
			}
		}
	}

	*decoded_vpath_end = '\0';
	*retval = decoded_vpath;
	*retval_len = decoded_vpath_end - decoded_vpath;
}