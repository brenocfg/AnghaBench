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
struct TYPE_2__ {int /*<<< orphan*/  NextEntryOffset; int /*<<< orphan*/  FileNameLength; } ;
typedef  TYPE_1__ FILE_DIRECTORY_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
num_entries(char *bufstart, char *end_of_buf, char **lastentry, size_t size)
{
	int len;
	unsigned int entrycount = 0;
	unsigned int next_offset = 0;
	char *entryptr;
	FILE_DIRECTORY_INFO *dir_info;

	if (bufstart == NULL)
		return 0;

	entryptr = bufstart;

	while (1) {
		if (entryptr + next_offset < entryptr ||
		    entryptr + next_offset > end_of_buf ||
		    entryptr + next_offset + size > end_of_buf) {
			cifs_dbg(VFS, "malformed search entry would overflow\n");
			break;
		}

		entryptr = entryptr + next_offset;
		dir_info = (FILE_DIRECTORY_INFO *)entryptr;

		len = le32_to_cpu(dir_info->FileNameLength);
		if (entryptr + len < entryptr ||
		    entryptr + len > end_of_buf ||
		    entryptr + len + size > end_of_buf) {
			cifs_dbg(VFS, "directory entry name would overflow frame end of buf %p\n",
				 end_of_buf);
			break;
		}

		*lastentry = entryptr;
		entrycount++;

		next_offset = le32_to_cpu(dir_info->NextEntryOffset);
		if (!next_offset)
			break;
	}

	return entrycount;
}