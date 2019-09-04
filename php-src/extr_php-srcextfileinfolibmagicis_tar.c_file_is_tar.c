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
struct magic_set {int flags; } ;
struct buffer {unsigned char* fbuf; size_t flen; } ;

/* Variables and functions */
 int MAGIC_APPLE ; 
 int MAGIC_EXTENSION ; 
 int MAGIC_MIME ; 
 int file_printf (struct magic_set*,char*,char*) ; 
 int is_tar (unsigned char const*,size_t) ; 
 char** tartype ; 

int
file_is_tar(struct magic_set *ms, const struct buffer *b)
{
	const unsigned char *buf = b->fbuf;
	size_t nbytes = b->flen;
	/*
	 * Do the tar test first, because if the first file in the tar
	 * archive starts with a dot, we can confuse it with an nroff file.
	 */
	int tar;
	int mime = ms->flags & MAGIC_MIME;

	if ((ms->flags & (MAGIC_APPLE|MAGIC_EXTENSION)) != 0)
		return 0;

	tar = is_tar(buf, nbytes);
	if (tar < 1 || tar > 3)
		return 0;

	if (file_printf(ms, "%s", mime ? "application/x-tar" :
	    tartype[tar - 1]) == -1)
		return -1;
	return 1;
}