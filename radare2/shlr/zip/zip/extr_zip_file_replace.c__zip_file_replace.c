#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zip_uint64_t ;
typedef  int zip_int64_t ;
typedef  int zip_flags_t ;
struct zip_source {int dummy; } ;
struct zip {scalar_t__ nentry; TYPE_1__* entry; int /*<<< orphan*/  error; } ;
struct TYPE_5__ {int changed; int /*<<< orphan*/  comp_method; } ;
struct TYPE_4__ {struct zip_source* source; TYPE_3__* changes; int /*<<< orphan*/ * orig; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_CM_REPLACED_DEFAULT ; 
 int ZIP_DIRENT_COMP_METHOD ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  ZIP_ER_RDONLY ; 
 int ZIP_FL_OVERWRITE ; 
 scalar_t__ ZIP_IS_RDONLY (struct zip*) ; 
 scalar_t__ ZIP_UINT64_MAX ; 
 int _zip_add_entry (struct zip*) ; 
 TYPE_3__* _zip_dirent_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zip_entry_finalize (TYPE_1__*) ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _zip_name_locate (struct zip*,char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ _zip_set_name (struct zip*,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  _zip_unchange_data (TYPE_1__*) ; 

zip_int64_t
_zip_file_replace(struct zip *za, zip_uint64_t idx, const char *name, struct zip_source *source, zip_flags_t flags)
{
    zip_uint64_t za_nentry_prev;
    
    if (ZIP_IS_RDONLY(za)) {
	_zip_error_set(&za->error, ZIP_ER_RDONLY, 0);
	return -1;
    }

    za_nentry_prev = za->nentry;
    if (idx == ZIP_UINT64_MAX) {
	zip_int64_t i = -1;
	
	if (flags & ZIP_FL_OVERWRITE)
	    i = _zip_name_locate(za, name, flags, NULL);

	if (i == -1) {
	    /* create and use new entry, used by zip_add */
	    if ((i=_zip_add_entry(za)) < 0)
		return -1;
	}
	idx = (zip_uint64_t)i;
    }
    
    if (name && _zip_set_name(za, idx, name, flags) != 0) {
	if (za->nentry != za_nentry_prev) {
	    _zip_entry_finalize(za->entry+idx);
	    za->nentry = za_nentry_prev;
	}
	return -1;
    }

    /* does not change any name related data, so we can do it here;
     * needed for a double add of the same file name */
    _zip_unchange_data(za->entry+idx);

    if (za->entry[idx].orig != NULL && (za->entry[idx].changes == NULL || (za->entry[idx].changes->changed & ZIP_DIRENT_COMP_METHOD) == 0)) {
        if (za->entry[idx].changes == NULL) {
            if ((za->entry[idx].changes=_zip_dirent_clone(za->entry[idx].orig)) == NULL) {
                _zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
                return -1;
            }
        }

        za->entry[idx].changes->comp_method = ZIP_CM_REPLACED_DEFAULT;
        za->entry[idx].changes->changed |= ZIP_DIRENT_COMP_METHOD;
    }
	
    za->entry[idx].source = source;

    return (zip_int64_t)idx;
}