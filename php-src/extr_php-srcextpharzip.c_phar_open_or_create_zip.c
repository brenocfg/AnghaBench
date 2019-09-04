#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int is_data; int is_zip; scalar_t__ is_tar; scalar_t__ internal_file_start; scalar_t__ is_brandnew; } ;
typedef  TYPE_1__ phar_archive_data ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int phar_create_or_parse_filename (char*,size_t,char*,size_t,int,int /*<<< orphan*/ ,TYPE_1__**,char**) ; 
 int /*<<< orphan*/  spprintf (char**,int,char*,char*) ; 

int phar_open_or_create_zip(char *fname, size_t fname_len, char *alias, size_t alias_len, int is_data, uint32_t options, phar_archive_data** pphar, char **error) /* {{{ */
{
	phar_archive_data *phar;
	int ret = phar_create_or_parse_filename(fname, fname_len, alias, alias_len, is_data, options, &phar, error);

	if (FAILURE == ret) {
		return FAILURE;
	}

	if (pphar) {
		*pphar = phar;
	}

	phar->is_data = is_data;

	if (phar->is_zip) {
		return ret;
	}

	if (phar->is_brandnew) {
		phar->internal_file_start = 0;
		phar->is_zip = 1;
		phar->is_tar = 0;
		return SUCCESS;
	}

	/* we've reached here - the phar exists and is a regular phar */
	if (error) {
		spprintf(error, 4096, "phar zip error: phar \"%s\" already exists as a regular phar and must be deleted from disk prior to creating as a zip-based phar", fname);
	}

	return FAILURE;
}