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
struct stat {scalar_t__ st_size; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF_S (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  F_CLI ; 
 int /*<<< orphan*/  F_NOTRACE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int TRUE ; 
 int /*<<< orphan*/  clearselection () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  copier ; 
 int create_tmp_file () ; 
 int /*<<< orphan*/  editor ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int /*<<< orphan*/ * g_tmpfpath ; 
 int nselected ; 
 int open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* pselbuf ; 
 size_t read (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetselind () ; 
 int /*<<< orphan*/  selbuflen ; 
 scalar_t__ selbufpos ; 
 int /*<<< orphan*/  seltofile (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spawn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writesel (char*,scalar_t__) ; 

__attribute__((used)) static bool editselection(void)
{
	bool ret = FALSE;
	int fd, lines = 0;
	ssize_t count;
	struct stat sb;

	if (!selbufpos) {
		DPRINTF_S("empty selection");
		return FALSE;
	}

	fd = create_tmp_file();
	if (fd == -1) {
		DPRINTF_S("couldn't create tmp file");
		return FALSE;
	}

	seltofile(fd, NULL);
	close(fd);

	spawn(editor, g_tmpfpath, NULL, NULL, F_CLI);

	fd = open(g_tmpfpath, O_RDONLY);
	if (fd == -1) {
		DPRINTF_S("couldn't read tmp file");
		unlink(g_tmpfpath);
		return FALSE;
	}

	fstat(fd, &sb);

	if (sb.st_size > selbufpos) {
		DPRINTF_S("edited buffer larger than pervious");
		goto emptyedit;
	}

	count = read(fd, pselbuf, selbuflen);
	close(fd);
	unlink(g_tmpfpath);

	if (!count) {
		ret = TRUE;
		goto emptyedit;
	}

	if (count < 0) {
		DPRINTF_S("error reading tmp file");
		goto emptyedit;
	}

	resetselind();
	selbufpos = count;
	/* The last character should be '\n' */
	pselbuf[--count] = '\0';
	for (--count; count > 0; --count) {
		/* Replace every '\n' that separates two paths */
		if (pselbuf[count] == '\n' && pselbuf[count + 1] == '/') {
			++lines;
			pselbuf[count] = '\0';
		}
	}

	/* Add a line for the last file */
	++lines;

	if (lines > nselected) {
		DPRINTF_S("files added to selection");
		goto emptyedit;
	}

	nselected = lines;
	writesel(pselbuf, selbufpos - 1);
	spawn(copier, NULL, NULL, NULL, F_NOTRACE);

	return TRUE;

emptyedit:
	resetselind();
	clearselection();
	return ret;
}