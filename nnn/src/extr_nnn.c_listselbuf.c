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
 int FALSE ; 
 int /*<<< orphan*/  F_CLI ; 
 int TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 int create_tmp_file () ; 
 int /*<<< orphan*/  g_tmpfpath ; 
 int /*<<< orphan*/  pager ; 
 size_t selbufpos ; 
 size_t seltofile (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spawn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool listselbuf(void)
{
	int fd;
	size_t pos;

	if (!selbufpos)
		return FALSE;

	fd = create_tmp_file();
	if (fd == -1)
		return FALSE;

	pos = seltofile(fd, NULL);

	close(fd);
	if (pos && pos == selbufpos)
		spawn(pager, g_tmpfpath, NULL, NULL, F_CLI);
	unlink(g_tmpfpath);

	return TRUE;
}