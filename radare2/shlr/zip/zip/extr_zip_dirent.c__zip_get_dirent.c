#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zip_uint64_t ;
typedef  int zip_flags_t ;
struct zip_error {int dummy; } ;
struct zip_dirent {int dummy; } ;
struct zip {size_t nentry; TYPE_1__* entry; struct zip_error error; } ;
struct TYPE_2__ {struct zip_dirent* changes; struct zip_dirent* orig; scalar_t__ deleted; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_DELETED ; 
 int /*<<< orphan*/  ZIP_ER_INVAL ; 
 int ZIP_FL_UNCHANGED ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct zip_dirent *
_zip_get_dirent(struct zip *za, zip_uint64_t idx, zip_flags_t flags, struct zip_error *error)
{
    if (error == NULL)
	error = &za->error;

    if (idx >= za->nentry) {
	_zip_error_set(error, ZIP_ER_INVAL, 0);
	return NULL;
    }

    if ((flags & ZIP_FL_UNCHANGED) || za->entry[idx].changes == NULL) {
	if (za->entry[idx].orig == NULL) {
	    _zip_error_set(error, ZIP_ER_INVAL, 0);
	    return NULL;
	}
	if (za->entry[idx].deleted && (flags & ZIP_FL_UNCHANGED) == 0) {
	    _zip_error_set(error, ZIP_ER_DELETED, 0);
	    return NULL;
	}
	return za->entry[idx].orig;
    }
    else
	return za->entry[idx].changes;
}