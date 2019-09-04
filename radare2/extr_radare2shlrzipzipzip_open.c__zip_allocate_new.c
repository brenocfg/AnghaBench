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
struct zip_error {int dummy; } ;
struct zip {unsigned int open_flags; int /*<<< orphan*/ * zn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 struct zip* _zip_new (struct zip_error*) ; 
 int /*<<< orphan*/  set_error (int*,struct zip_error*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  zip_discard (struct zip*) ; 

__attribute__((used)) static struct zip *
_zip_allocate_new(const char *fn, unsigned int flags, int *zep)
{
    struct zip *za;
    struct zip_error error;

    if ((za=_zip_new(&error)) == NULL) {
	set_error(zep, &error, 0);
	return NULL;
    }

    if (fn == NULL)
	za->zn = NULL;
    else {
	za->zn = strdup(fn);
	if (!za->zn) {
	    zip_discard(za);
	    set_error(zep, NULL, ZIP_ER_MEMORY);
	    return NULL;
	}
    }
    za->open_flags = flags;
    return za;
}