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
struct zip_dirent {int changed; int /*<<< orphan*/  comment; int /*<<< orphan*/  cloned; int /*<<< orphan*/  extra_fields; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int ZIP_DIRENT_COMMENT ; 
 int ZIP_DIRENT_EXTRA_FIELD ; 
 int ZIP_DIRENT_FILENAME ; 
 int /*<<< orphan*/  _zip_ef_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zip_string_free (int /*<<< orphan*/ ) ; 

void
_zip_dirent_finalize(struct zip_dirent *zde)
{
    if (!zde->cloned || zde->changed & ZIP_DIRENT_FILENAME)
	_zip_string_free(zde->filename);
    if (!zde->cloned || zde->changed & ZIP_DIRENT_EXTRA_FIELD)
	_zip_ef_free(zde->extra_fields);
    if (!zde->cloned || zde->changed & ZIP_DIRENT_COMMENT)
	_zip_string_free(zde->comment);
}