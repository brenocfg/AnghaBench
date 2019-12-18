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
struct xen_snd_front_pcm_stream_info {size_t buffer_sz; int num_pages; scalar_t__ buffer; int /*<<< orphan*/ * pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (size_t,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ alloc_pages_exact (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 

__attribute__((used)) static int shbuf_setup_backstore(struct xen_snd_front_pcm_stream_info *stream,
				 size_t buffer_sz)
{
	int i;

	stream->buffer = alloc_pages_exact(buffer_sz, GFP_KERNEL);
	if (!stream->buffer)
		return -ENOMEM;

	stream->buffer_sz = buffer_sz;
	stream->num_pages = DIV_ROUND_UP(stream->buffer_sz, PAGE_SIZE);
	stream->pages = kcalloc(stream->num_pages, sizeof(struct page *),
				GFP_KERNEL);
	if (!stream->pages)
		return -ENOMEM;

	for (i = 0; i < stream->num_pages; i++)
		stream->pages[i] = virt_to_page(stream->buffer + i * PAGE_SIZE);

	return 0;
}