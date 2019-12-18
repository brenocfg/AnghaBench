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
struct xen_snd_front_pcm_stream_info {int /*<<< orphan*/  pages; int /*<<< orphan*/  buffer_sz; scalar_t__ buffer; int /*<<< orphan*/  shbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages_exact (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_clear (struct xen_snd_front_pcm_stream_info*) ; 
 int /*<<< orphan*/  xen_front_pgdir_shbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_front_pgdir_shbuf_unmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stream_free(struct xen_snd_front_pcm_stream_info *stream)
{
	xen_front_pgdir_shbuf_unmap(&stream->shbuf);
	xen_front_pgdir_shbuf_free(&stream->shbuf);
	if (stream->buffer)
		free_pages_exact(stream->buffer, stream->buffer_sz);
	kfree(stream->pages);
	stream_clear(stream);
}