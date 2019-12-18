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
struct splice_pipe_desc {int dummy; } ;
struct sock {int dummy; } ;
struct pipe_inode_info {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int min (unsigned int,unsigned int) ; 
 scalar_t__ spd_fill_page (struct splice_pipe_desc*,struct pipe_inode_info*,struct page*,unsigned int*,unsigned int,int,struct sock*) ; 

__attribute__((used)) static bool __splice_segment(struct page *page, unsigned int poff,
			     unsigned int plen, unsigned int *off,
			     unsigned int *len,
			     struct splice_pipe_desc *spd, bool linear,
			     struct sock *sk,
			     struct pipe_inode_info *pipe)
{
	if (!*len)
		return true;

	/* skip this segment if already processed */
	if (*off >= plen) {
		*off -= plen;
		return false;
	}

	/* ignore any bits we already processed */
	poff += *off;
	plen -= *off;
	*off = 0;

	do {
		unsigned int flen = min(*len, plen);

		if (spd_fill_page(spd, pipe, page, &flen, poff,
				  linear, sk))
			return true;
		poff += flen;
		plen -= flen;
		*len -= flen;
	} while (*len && plen);

	return false;
}