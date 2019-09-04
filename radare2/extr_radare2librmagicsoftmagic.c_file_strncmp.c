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
typedef  char ut64 ;
typedef  long ut32 ;

/* Variables and functions */
 long STRING_COMPACT_BLANK ; 
 long STRING_COMPACT_OPTIONAL_BLANK ; 
 long STRING_IGNORE_LOWERCASE ; 
 long STRING_IGNORE_UPPERCASE ; 
 scalar_t__ islower (int /*<<< orphan*/  const) ; 
 scalar_t__ isspace (int /*<<< orphan*/  const) ; 
 scalar_t__ isupper (int /*<<< orphan*/  const) ; 
 char tolower (int /*<<< orphan*/ ) ; 
 char toupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut64 file_strncmp(const char *s1, const char *s2, size_t len, ut32 flags) {
	/*
	 * Convert the source args to unsigned here so that (1) the
	 * compare will be unsigned as it is in strncmp() and (2) so
	 * the ctype functions will work correctly without extra
	 * casting.
	 */
	const ut8 *a = (const ut8 *)s1;
	const ut8 *b = (const ut8 *)s2;
	ut64 v;

	/*
	 * What we want here is v = strncmp(s1, s2, len),
	 * but ignoring any nulls.
	 */
	v = 0;
	if (0L == flags) { /* normal string: do it fast */
		while (len-- > 0) {
			if ((v = *b++ - *a++) != '\0') {
				break;
			}
		}
	} else { /* combine the others */
		while (len-- > 0) {
			if ((flags & STRING_IGNORE_LOWERCASE) &&
			    islower(*a)) {
				if ((v = tolower (*b++) - *a++) != '\0') {
					break;
				}
			} else if ((flags & STRING_IGNORE_UPPERCASE) && isupper(*a)) {
				if ((v = toupper (*b++) - *a++) != '\0') {
					break;
				}
			} else if ((flags & STRING_COMPACT_BLANK) && isspace(*a)) {
				a++;
				if (isspace(*b++)) {
					while (isspace (*b)) {
						b++;
					}
				} else {
					v = 1;
					break;
				}
			} else if ((flags & STRING_COMPACT_OPTIONAL_BLANK) && isspace(*a)) {
				a++;
				while (isspace (*b)) {
					b++;
				}
			} else {
				if ((v = *b++ - *a++) != '\0') {
					break;
				}
			}
		}
	}
	return v;
}