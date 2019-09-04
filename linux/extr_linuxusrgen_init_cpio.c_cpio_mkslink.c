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
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 unsigned int S_IFLNK ; 
 scalar_t__ default_mtime ; 
 int /*<<< orphan*/  ino ; 
 int /*<<< orphan*/  push_hdr (char*) ; 
 int /*<<< orphan*/  push_pad () ; 
 int /*<<< orphan*/  push_string (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ,unsigned int,long,long,int,long,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int cpio_mkslink(const char *name, const char *target,
			 unsigned int mode, uid_t uid, gid_t gid)
{
	char s[256];

	if (name[0] == '/')
		name++;
	sprintf(s,"%s%08X%08X%08lX%08lX%08X%08lX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		"070701",		/* magic */
		ino++,			/* ino */
		S_IFLNK | mode,		/* mode */
		(long) uid,		/* uid */
		(long) gid,		/* gid */
		1,			/* nlink */
		(long) default_mtime,	/* mtime */
		(unsigned)strlen(target)+1, /* filesize */
		3,			/* major */
		1,			/* minor */
		0,			/* rmajor */
		0,			/* rminor */
		(unsigned)strlen(name) + 1,/* namesize */
		0);			/* chksum */
	push_hdr(s);
	push_string(name);
	push_pad();
	push_string(target);
	push_pad();
	return 0;
}