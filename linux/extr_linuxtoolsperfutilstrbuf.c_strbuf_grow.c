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
struct strbuf {size_t len; size_t alloc; char* buf; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 size_t alloc_nr (size_t) ; 
 char* realloc (char*,size_t) ; 

int strbuf_grow(struct strbuf *sb, size_t extra)
{
	char *buf;
	size_t nr = sb->len + extra + 1;

	if (nr < sb->alloc)
		return 0;

	if (nr <= sb->len)
		return -E2BIG;

	if (alloc_nr(sb->alloc) > nr)
		nr = alloc_nr(sb->alloc);

	/*
	 * Note that sb->buf == strbuf_slopbuf if sb->alloc == 0, and it is
	 * a static variable. Thus we have to avoid passing it to realloc.
	 */
	buf = realloc(sb->alloc ? sb->buf : NULL, nr * sizeof(*buf));
	if (!buf)
		return -ENOMEM;

	sb->buf = buf;
	sb->alloc = nr;
	return 0;
}