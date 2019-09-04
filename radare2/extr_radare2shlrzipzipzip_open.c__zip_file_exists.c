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
struct stat {int dummy; } ;

/* Variables and functions */
 unsigned int ZIP_CREATE ; 
 int /*<<< orphan*/  ZIP_ER_EXISTS ; 
 int /*<<< orphan*/  ZIP_ER_INVAL ; 
 int /*<<< orphan*/  ZIP_ER_OPEN ; 
 unsigned int ZIP_EXCL ; 
 int /*<<< orphan*/  set_error (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int
_zip_file_exists(const char *fn, unsigned int flags, int *zep)
{
    struct stat st;

    if (fn == NULL) {
	set_error(zep, NULL, ZIP_ER_INVAL);
	return -1;
    }
    
    if (stat(fn, &st) != 0) {
	if (flags & ZIP_CREATE)
	    return 0;
	else {
	    set_error(zep, NULL, ZIP_ER_OPEN);
	    return -1;
	}
    }
    else if ((flags & ZIP_EXCL)) {
	set_error(zep, NULL, ZIP_ER_EXISTS);
	return -1;
    }
    /* ZIP_CREATE gets ignored if file exists and not ZIP_EXCL,
       just like open() */

    return 1;
}