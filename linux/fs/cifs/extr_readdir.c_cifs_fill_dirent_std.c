#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cifs_dirent {int /*<<< orphan*/  resume_key; int /*<<< orphan*/  namelen; int /*<<< orphan*/ * name; } ;
struct TYPE_3__ {int /*<<< orphan*/  ResumeKey; int /*<<< orphan*/  FileNameLength; int /*<<< orphan*/ * FileName; } ;
typedef  TYPE_1__ FIND_FILE_STANDARD_INFO ;

/* Variables and functions */

__attribute__((used)) static void cifs_fill_dirent_std(struct cifs_dirent *de,
		const FIND_FILE_STANDARD_INFO *info)
{
	de->name = &info->FileName[0];
	/* one byte length, no endianess conversion */
	de->namelen = info->FileNameLength;
	de->resume_key = info->ResumeKey;
}