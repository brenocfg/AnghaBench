#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cifs_dirent {int /*<<< orphan*/  ino; int /*<<< orphan*/  resume_key; int /*<<< orphan*/ * name; int /*<<< orphan*/  namelen; } ;
struct TYPE_4__ {int /*<<< orphan*/  UniqueId; } ;
struct TYPE_5__ {TYPE_1__ basic; int /*<<< orphan*/  ResumeKey; int /*<<< orphan*/ * FileName; } ;
typedef  TYPE_2__ FILE_UNIX_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  cifs_unicode_bytelen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strnlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cifs_fill_dirent_unix(struct cifs_dirent *de,
		const FILE_UNIX_INFO *info, bool is_unicode)
{
	de->name = &info->FileName[0];
	if (is_unicode)
		de->namelen = cifs_unicode_bytelen(de->name);
	else
		de->namelen = strnlen(de->name, PATH_MAX);
	de->resume_key = info->ResumeKey;
	de->ino = le64_to_cpu(info->basic.UniqueId);
}