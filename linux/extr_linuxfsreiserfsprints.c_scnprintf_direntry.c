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
struct reiserfs_dir_entry {int de_namelen; int /*<<< orphan*/  de_objectid; int /*<<< orphan*/  de_dir_id; int /*<<< orphan*/  de_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int scnprintf (char*,size_t,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scnprintf_direntry(char *buf, size_t size,
			      struct reiserfs_dir_entry *de)
{
	char name[20];

	memcpy(name, de->de_name, de->de_namelen > 19 ? 19 : de->de_namelen);
	name[de->de_namelen > 19 ? 19 : de->de_namelen] = 0;
	return scnprintf(buf, size, "\"%s\"==>[%d %d]",
			 name, de->de_dir_id, de->de_objectid);
}