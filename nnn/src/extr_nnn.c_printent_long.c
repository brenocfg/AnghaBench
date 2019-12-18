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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  timebuf ;
struct entry {int flags; int mode; int blocks; int size; int /*<<< orphan*/  name; int /*<<< orphan*/  t; } ;
struct TYPE_2__ {int /*<<< orphan*/  blkorder; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_REVERSE ; 
 int FILE_SELECTED ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  attroff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attron (int /*<<< orphan*/ ) ; 
 int blk_shift ; 
 TYPE_1__ cfg ; 
 int /*<<< orphan*/  coolsize (int) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printw (char*,char const,char*,char*,...) ; 
 int /*<<< orphan*/  resetdircolor (int) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* unescape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void printent_long(const struct entry *ent, int sel, uint namecols)
{
	char timebuf[24], permbuf[4], ind1 = '\0', ind2[] = "\0\0";
	const char cp = (ent->flags & FILE_SELECTED) ? '+' : ' ';

	/* Timestamp */
	strftime(timebuf, sizeof(timebuf), "%F %R", localtime(&ent->t));
	timebuf[sizeof(timebuf)-1] = '\0';

	/* Permissions */
	permbuf[0] = '0' + ((ent->mode >> 6) & 7);
	permbuf[1] = '0' + ((ent->mode >> 3) & 7);
	permbuf[2] = '0' + (ent->mode & 7);
	permbuf[3] = '\0';

	/* Add a column if no indicator is needed */
	if (S_ISREG(ent->mode) && !(ent->mode & 0100))
		++namecols;

	/* Trim escape chars from name */
	const char *pname = unescape(ent->name, namecols, NULL);

	/* Directories are always shown on top */
	resetdircolor(ent->flags);

	if (sel)
		attron(A_REVERSE);

	switch (ent->mode & S_IFMT) {
	case S_IFREG:
		if (ent->mode & 0100)
			printw("%c%-16.16s  %s %8.8s* %s*\n", cp, timebuf, permbuf,
			       coolsize(cfg.blkorder ? ent->blocks << blk_shift : ent->size), pname);
		else
			printw("%c%-16.16s  %s %8.8s  %s\n", cp, timebuf, permbuf,
			       coolsize(cfg.blkorder ? ent->blocks << blk_shift : ent->size), pname);
		break;
	case S_IFDIR:
		printw("%c%-16.16s  %s %8.8s  %s/\n", cp, timebuf, permbuf,
		       coolsize(cfg.blkorder ? ent->blocks << blk_shift : ent->size), pname);
		break;
	case S_IFLNK:
		printw("%c%-16.16s  %s        @  %s@\n", cp, timebuf, permbuf, pname);
		break;
	case S_IFSOCK:
		ind1 = ind2[0] = '='; // fallthrough
	case S_IFIFO:
		if (!ind1)
			ind1 = ind2[0] = '|'; // fallthrough
	case S_IFBLK:
		if (!ind1)
			ind1 = 'b'; // fallthrough
	case S_IFCHR:
		if (!ind1)
			ind1 = 'c'; // fallthrough
	default:
		if (!ind1)
			ind1 = ind2[0] = '?';
		printw("%c%-16.16s  %s        %c  %s%s\n", cp, timebuf, permbuf, ind1, pname, ind2);
		break;
	}

	if (sel)
		attroff(A_REVERSE);
}