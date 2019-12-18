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
struct TYPE_3__ {int /*<<< orphan*/  FileIndex; int /*<<< orphan*/  FileNameLength; int /*<<< orphan*/ * FileName; } ;
typedef  TYPE_1__ FILE_BOTH_DIRECTORY_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cifs_fill_dirent_both(struct cifs_dirent *de,
		const FILE_BOTH_DIRECTORY_INFO *info)
{
	de->name = &info->FileName[0];
	de->namelen = le32_to_cpu(info->FileNameLength);
	de->resume_key = info->FileIndex;
}