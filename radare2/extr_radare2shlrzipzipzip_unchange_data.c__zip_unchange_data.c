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
struct zip_entry {scalar_t__ deleted; TYPE_1__* changes; int /*<<< orphan*/ * source; } ;
struct TYPE_2__ {int changed; scalar_t__ comp_method; } ;

/* Variables and functions */
 scalar_t__ ZIP_CM_REPLACED_DEFAULT ; 
 int ZIP_DIRENT_COMP_METHOD ; 
 int /*<<< orphan*/  _zip_dirent_free (TYPE_1__*) ; 
 int /*<<< orphan*/  zip_source_free (int /*<<< orphan*/ *) ; 

void
_zip_unchange_data(struct zip_entry *ze)
{
    if (ze->source) {
	zip_source_free(ze->source);
	ze->source = NULL;
    }

    if (ze->changes != NULL && (ze->changes->changed & ZIP_DIRENT_COMP_METHOD) && ze->changes->comp_method == ZIP_CM_REPLACED_DEFAULT) {
	ze->changes->changed &= ~ZIP_DIRENT_COMP_METHOD;
	if (ze->changes->changed == 0) {
	    _zip_dirent_free(ze->changes);
	    ze->changes = NULL;
	}
    }

    ze->deleted = 0;
}