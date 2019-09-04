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
struct splice_pipe_desc {unsigned int nr_pages_max; void* partial; void* pages; } ;
struct pipe_inode_info {int /*<<< orphan*/  buffers; } ;
struct partial_page {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PIPE_DEF_BUFFERS ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

int splice_grow_spd(const struct pipe_inode_info *pipe, struct splice_pipe_desc *spd)
{
	unsigned int buffers = READ_ONCE(pipe->buffers);

	spd->nr_pages_max = buffers;
	if (buffers <= PIPE_DEF_BUFFERS)
		return 0;

	spd->pages = kmalloc_array(buffers, sizeof(struct page *), GFP_KERNEL);
	spd->partial = kmalloc_array(buffers, sizeof(struct partial_page),
				     GFP_KERNEL);

	if (spd->pages && spd->partial)
		return 0;

	kfree(spd->pages);
	kfree(spd->partial);
	return -ENOMEM;
}