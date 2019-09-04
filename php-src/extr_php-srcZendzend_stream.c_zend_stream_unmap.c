#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  old_handle; scalar_t__ buf; scalar_t__ map; scalar_t__ pos; scalar_t__ len; } ;
struct TYPE_5__ {TYPE_1__ mmap; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ zend_stream ;

/* Variables and functions */
 int /*<<< orphan*/  efree (scalar_t__) ; 

__attribute__((used)) static void zend_stream_unmap(zend_stream *stream) { /* {{{ */
#if HAVE_MMAP
	if (stream->mmap.map) {
		munmap(stream->mmap.map, stream->mmap.len + ZEND_MMAP_AHEAD);
	} else
#endif
	if (stream->mmap.buf) {
		efree(stream->mmap.buf);
	}
	stream->mmap.len = 0;
	stream->mmap.pos = 0;
	stream->mmap.map = 0;
	stream->mmap.buf = 0;
	stream->handle   = stream->mmap.old_handle;
}