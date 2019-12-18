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
 int SDB_LIKE_BASE64 ; 
 int SDB_LIKE_END ; 
 int SDB_LIKE_ICASE ; 
 int SDB_LIKE_START ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mycmp (char const*,char const*,int,int) ; 
 scalar_t__ sdb_decode (char const*,int*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 int strstr2 (char const*,char const*,int) ; 

__attribute__((used)) static inline bool compareString(const char *a, const char *b, int blen, int flags) {
	const int start = flags & SDB_LIKE_START;
	const int end = flags & SDB_LIKE_END;
	char *aa = NULL;
	int alen;
	bool ret = false;
	if (!a || !b || blen < 0) {
		return 0;
	}
	if (flags & SDB_LIKE_BASE64) {
		aa = (char*)sdb_decode (a, &alen);
		if (!aa) {
			return 0;
		}
		a = (const char *)aa;
	} else {
		alen = strlen (a);
	}
	if (blen <= alen) {
		if (flags & SDB_LIKE_ICASE) {
			if (start && end) ret = (alen==blen && !mycmp (a, b, blen, 0));
			else if (start) ret = !mycmp (a, b, blen, 0);
			else if (end) ret = !mycmp (a+(alen-blen), b, blen, 0);
			else ret = !mycmp (a, b, blen, 1);
		} else {
			if (start && end) ret = (alen==blen && !strncmp (a, b, blen));
			else if (start) ret = !strncmp (a, b, blen);
			else if (end) ret = !strncmp (a+(alen-blen), b, blen);
			else ret = strstr2 (a, b, blen);
		}
	}
	free (aa);
	return ret;
}