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

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_CMD_LEN ; 
 size_t ATOOL ; 
 size_t BSDTAR ; 
 scalar_t__ getutil (int /*<<< orphan*/ ) ; 
 scalar_t__ is_suffix (char*,char*) ; 
 int /*<<< orphan*/ * utils ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_archive_cmd(char *cmd, char *archive)
{
	if (getutil(utils[ATOOL]))
		xstrlcpy(cmd, "atool -a", ARCHIVE_CMD_LEN);
	else if (getutil(utils[BSDTAR]))
		xstrlcpy(cmd, "bsdtar -acvf", ARCHIVE_CMD_LEN);
	else if (is_suffix(archive, ".zip"))
		xstrlcpy(cmd, "zip -r", ARCHIVE_CMD_LEN);
	else
		xstrlcpy(cmd, "tar -acvf", ARCHIVE_CMD_LEN);
}