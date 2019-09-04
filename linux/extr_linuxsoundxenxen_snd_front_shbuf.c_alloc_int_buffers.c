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
struct xen_snd_front_shbuf {int buffer_sz; int /*<<< orphan*/ * directory; int /*<<< orphan*/ * grefs; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int XEN_PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_pages_exact (int,int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_int_buffers(struct xen_snd_front_shbuf *buf,
			     int num_pages_dir, int num_pages_buffer,
			     int num_grefs)
{
	buf->grefs = kcalloc(num_grefs, sizeof(*buf->grefs), GFP_KERNEL);
	if (!buf->grefs)
		return -ENOMEM;

	buf->directory = kcalloc(num_pages_dir, XEN_PAGE_SIZE, GFP_KERNEL);
	if (!buf->directory)
		goto fail;

	buf->buffer_sz = num_pages_buffer * XEN_PAGE_SIZE;
	buf->buffer = alloc_pages_exact(buf->buffer_sz, GFP_KERNEL);
	if (!buf->buffer)
		goto fail;

	return 0;

fail:
	kfree(buf->grefs);
	buf->grefs = NULL;
	kfree(buf->directory);
	buf->directory = NULL;
	return -ENOMEM;
}