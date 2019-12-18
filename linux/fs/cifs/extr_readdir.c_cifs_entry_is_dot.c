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
struct cifs_dirent {char* name; int namelen; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 scalar_t__ UNICODE_DOT ; 

__attribute__((used)) static int cifs_entry_is_dot(struct cifs_dirent *de, bool is_unicode)
{
	int rc = 0;

	if (!de->name)
		return 0;

	if (is_unicode) {
		__le16 *ufilename = (__le16 *)de->name;
		if (de->namelen == 2) {
			/* check for . */
			if (ufilename[0] == UNICODE_DOT)
				rc = 1;
		} else if (de->namelen == 4) {
			/* check for .. */
			if (ufilename[0] == UNICODE_DOT &&
			    ufilename[1] == UNICODE_DOT)
				rc = 2;
		}
	} else /* ASCII */ {
		if (de->namelen == 1) {
			if (de->name[0] == '.')
				rc = 1;
		} else if (de->namelen == 2) {
			if (de->name[0] == '.' && de->name[1] == '.')
				rc = 2;
		}
	}

	return rc;
}