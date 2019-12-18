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
typedef  int mode_t ;

/* Variables and functions */
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 

__attribute__((used)) static char get_fileind(mode_t mode)
{
	char c = '\0';

	switch (mode & S_IFMT) {
	case S_IFREG:
		c = '-';
		break;
	case S_IFDIR:
		c = 'd';
		break;
	case S_IFLNK:
		c = 'l';
		break;
	case S_IFSOCK:
		c = 's';
		break;
	case S_IFIFO:
		c = 'p';
		break;
	case S_IFBLK:
		c = 'b';
		break;
	case S_IFCHR:
		c = 'c';
		break;
	default:
		c = '?';
		break;
	}

	return c;
}