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
struct xenbus_device {int dummy; } ;
struct xen_snd_front_shbuf {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XENSND_NUM_GREFS_PER_PAGE ; 
 int /*<<< orphan*/  XEN_PAGE_SIZE ; 
 int alloc_int_buffers (struct xen_snd_front_shbuf*,int,int,int) ; 
 int /*<<< orphan*/  fill_page_dir (struct xen_snd_front_shbuf*,int) ; 
 int grant_references (struct xenbus_device*,struct xen_snd_front_shbuf*,int,int,int) ; 
 int /*<<< orphan*/  xen_snd_front_shbuf_clear (struct xen_snd_front_shbuf*) ; 

int xen_snd_front_shbuf_alloc(struct xenbus_device *xb_dev,
			      struct xen_snd_front_shbuf *buf,
			      unsigned int buffer_sz)
{
	int num_pages_buffer, num_pages_dir, num_grefs;
	int ret;

	xen_snd_front_shbuf_clear(buf);

	num_pages_buffer = DIV_ROUND_UP(buffer_sz, XEN_PAGE_SIZE);
	/* number of pages the page directory consumes itself */
	num_pages_dir = DIV_ROUND_UP(num_pages_buffer,
				     XENSND_NUM_GREFS_PER_PAGE);
	num_grefs = num_pages_buffer + num_pages_dir;

	ret = alloc_int_buffers(buf, num_pages_dir,
				num_pages_buffer, num_grefs);
	if (ret < 0)
		return ret;

	ret = grant_references(xb_dev, buf, num_pages_dir, num_pages_buffer,
			       num_grefs);
	if (ret < 0)
		return ret;

	fill_page_dir(buf, num_pages_dir);
	return 0;
}