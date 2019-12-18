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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  uint ;
struct entry {int mode; int flags; int /*<<< orphan*/  name; } ;

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
 int /*<<< orphan*/  addch (char) ; 
 int /*<<< orphan*/  addwstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attroff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attron (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetdircolor (int) ; 
 int /*<<< orphan*/  unescape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void printent(const struct entry *ent, int sel, uint namecols)
{
	wchar_t *wstr;
	char ind = '\0';

	switch (ent->mode & S_IFMT) {
	case S_IFREG:
		if (ent->mode & 0100)
			ind = '*';
		break;
	case S_IFDIR:
		ind = '/';
		break;
	case S_IFLNK:
		ind = '@';
		break;
	case S_IFSOCK:
		ind = '=';
		break;
	case S_IFIFO:
		ind = '|';
		break;
	case S_IFBLK: // fallthrough
	case S_IFCHR:
		break;
	default:
		ind = '?';
		break;
	}

	if (!ind)
		++namecols;

	unescape(ent->name, namecols, &wstr);

	/* Directories are always shown on top */
	resetdircolor(ent->flags);

	if (sel)
		attron(A_REVERSE);

	addch((ent->flags & FILE_SELECTED) ? '+' : ' ');
	addwstr(wstr);
	if (ind)
		addch(ind);
	addch('\n');

	if (sel)
		attroff(A_REVERSE);
}