#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ fp_type; char tar_type; TYPE_1__* phar; scalar_t__ fp_refcount; TYPE_3__* link; scalar_t__ is_tar; int /*<<< orphan*/  is_zip; scalar_t__ is_dir; scalar_t__ is_deleted; scalar_t__ is_modified; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_24__ {int for_write; void* zero; int /*<<< orphan*/ * fp; scalar_t__ is_tar; int /*<<< orphan*/  is_zip; TYPE_2__* internal_file; TYPE_4__* phar; scalar_t__ position; } ;
typedef  TYPE_3__ phar_entry_data ;
struct TYPE_25__ {scalar_t__ is_persistent; scalar_t__ is_data; } ;
typedef  TYPE_4__ phar_archive_data ;
struct TYPE_22__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ PHAR_G (int /*<<< orphan*/ ) ; 
 scalar_t__ PHAR_MOD ; 
 int /*<<< orphan*/  SEEK_END ; 
 int SUCCESS ; 
 char TAR_FILE ; 
 int /*<<< orphan*/  efree (TYPE_3__*) ; 
 scalar_t__ emalloc (int) ; 
 int phar_copy_on_write (TYPE_4__**) ; 
 int phar_create_writeable_entry (TYPE_4__*,TYPE_2__*,char**) ; 
 int phar_get_archive (TYPE_4__**,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * phar_get_efp (TYPE_2__*,int) ; 
 TYPE_2__* phar_get_entry_info (TYPE_4__*,char*,size_t,char**,int) ; 
 TYPE_2__* phar_get_entry_info_dir (TYPE_4__*,char*,size_t,char,char**,int) ; 
 void* phar_get_fp_offset (TYPE_2__*) ; 
 TYPE_2__* phar_get_link_source (TYPE_2__*) ; 
 int phar_open_entry_fp (TYPE_2__*,char**,int) ; 
 int /*<<< orphan*/  phar_seek_efp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phar_separate_entry_fp (TYPE_2__*,char**) ; 
 int /*<<< orphan*/  readonly ; 
 int /*<<< orphan*/  spprintf (char**,int,char*,char*,...) ; 

int phar_get_entry_data(phar_entry_data **ret, char *fname, size_t fname_len, char *path, size_t path_len, const char *mode, char allow_dir, char **error, int security) /* {{{ */
{
	phar_archive_data *phar;
	phar_entry_info *entry;
	int for_write  = mode[0] != 'r' || mode[1] == '+';
	int for_append = mode[0] == 'a';
	int for_create = mode[0] != 'r';
	int for_trunc  = mode[0] == 'w';

	if (!ret) {
		return FAILURE;
	}

	*ret = NULL;

	if (error) {
		*error = NULL;
	}

	if (FAILURE == phar_get_archive(&phar, fname, fname_len, NULL, 0, error)) {
		return FAILURE;
	}

	if (for_write && PHAR_G(readonly) && !phar->is_data) {
		if (error) {
			spprintf(error, 4096, "phar error: file \"%s\" in phar \"%s\" cannot be opened for writing, disabled by ini setting", path, fname);
		}
		return FAILURE;
	}

	if (!path_len) {
		if (error) {
			spprintf(error, 4096, "phar error: file \"\" in phar \"%s\" cannot be empty", fname);
		}
		return FAILURE;
	}
really_get_entry:
	if (allow_dir) {
		if ((entry = phar_get_entry_info_dir(phar, path, path_len, allow_dir, for_create && !PHAR_G(readonly) && !phar->is_data ? NULL : error, security)) == NULL) {
			if (for_create && (!PHAR_G(readonly) || phar->is_data)) {
				return SUCCESS;
			}
			return FAILURE;
		}
	} else {
		if ((entry = phar_get_entry_info(phar, path, path_len, for_create && !PHAR_G(readonly) && !phar->is_data ? NULL : error, security)) == NULL) {
			if (for_create && (!PHAR_G(readonly) || phar->is_data)) {
				return SUCCESS;
			}
			return FAILURE;
		}
	}

	if (for_write && phar->is_persistent) {
		if (FAILURE == phar_copy_on_write(&phar)) {
			if (error) {
				spprintf(error, 4096, "phar error: file \"%s\" in phar \"%s\" cannot be opened for writing, could not make cached phar writeable", path, fname);
			}
			return FAILURE;
		} else {
			goto really_get_entry;
		}
	}

	if (entry->is_modified && !for_write) {
		if (error) {
			spprintf(error, 4096, "phar error: file \"%s\" in phar \"%s\" cannot be opened for reading, writable file pointers are open", path, fname);
		}
		return FAILURE;
	}

	if (entry->fp_refcount && for_write) {
		if (error) {
			spprintf(error, 4096, "phar error: file \"%s\" in phar \"%s\" cannot be opened for writing, readable file pointers are open", path, fname);
		}
		return FAILURE;
	}

	if (entry->is_deleted) {
		if (!for_create) {
			return FAILURE;
		}
		entry->is_deleted = 0;
	}

	if (entry->is_dir) {
		*ret = (phar_entry_data *) emalloc(sizeof(phar_entry_data));
		(*ret)->position = 0;
		(*ret)->fp = NULL;
		(*ret)->phar = phar;
		(*ret)->for_write = for_write;
		(*ret)->internal_file = entry;
		(*ret)->is_zip = entry->is_zip;
		(*ret)->is_tar = entry->is_tar;

		if (!phar->is_persistent) {
			++(entry->phar->refcount);
			++(entry->fp_refcount);
		}

		return SUCCESS;
	}

	if (entry->fp_type == PHAR_MOD) {
		if (for_trunc) {
			if (FAILURE == phar_create_writeable_entry(phar, entry, error)) {
				return FAILURE;
			}
		} else if (for_append) {
			phar_seek_efp(entry, 0, SEEK_END, 0, 0);
		}
	} else {
		if (for_write) {
			if (entry->link) {
				efree(entry->link);
				entry->link = NULL;
				entry->tar_type = (entry->is_tar ? TAR_FILE : '\0');
			}

			if (for_trunc) {
				if (FAILURE == phar_create_writeable_entry(phar, entry, error)) {
					return FAILURE;
				}
			} else {
				if (FAILURE == phar_separate_entry_fp(entry, error)) {
					return FAILURE;
				}
			}
		} else {
			if (FAILURE == phar_open_entry_fp(entry, error, 1)) {
				return FAILURE;
			}
		}
	}

	*ret = (phar_entry_data *) emalloc(sizeof(phar_entry_data));
	(*ret)->position = 0;
	(*ret)->phar = phar;
	(*ret)->for_write = for_write;
	(*ret)->internal_file = entry;
	(*ret)->is_zip = entry->is_zip;
	(*ret)->is_tar = entry->is_tar;
	(*ret)->fp = phar_get_efp(entry, 1);
	if (entry->link) {
		phar_entry_info *link = phar_get_link_source(entry);
		if(!link) {
			efree(*ret);
			return FAILURE;
		}
		(*ret)->zero = phar_get_fp_offset(link);
	} else {
		(*ret)->zero = phar_get_fp_offset(entry);
	}

	if (!phar->is_persistent) {
		++(entry->fp_refcount);
		++(entry->phar->refcount);
	}

	return SUCCESS;
}