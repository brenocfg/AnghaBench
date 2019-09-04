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
struct cifs_dirent {int /*<<< orphan*/  resume_key; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  resume_key; int /*<<< orphan*/  resume_name_len; int /*<<< orphan*/  presume_name; int /*<<< orphan*/  unicode; int /*<<< orphan*/  info_level; } ;
struct cifsFileInfo {TYPE_1__ srch_inf; } ;

/* Variables and functions */
 int cifs_fill_dirent (struct cifs_dirent*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cifs_save_resume_key(const char *current_entry,
	struct cifsFileInfo *file_info)
{
	struct cifs_dirent de;
	int rc;

	rc = cifs_fill_dirent(&de, current_entry, file_info->srch_inf.info_level,
			      file_info->srch_inf.unicode);
	if (!rc) {
		file_info->srch_inf.presume_name = de.name;
		file_info->srch_inf.resume_name_len = de.namelen;
		file_info->srch_inf.resume_key = de.resume_key;
	}
	return rc;
}