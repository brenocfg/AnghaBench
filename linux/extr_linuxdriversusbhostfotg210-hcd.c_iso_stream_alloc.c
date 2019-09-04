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
struct fotg210_iso_stream {int next_uframe; int /*<<< orphan*/  free_list; int /*<<< orphan*/  td_list; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct fotg210_iso_stream* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fotg210_iso_stream *iso_stream_alloc(gfp_t mem_flags)
{
	struct fotg210_iso_stream *stream;

	stream = kzalloc(sizeof(*stream), mem_flags);
	if (likely(stream != NULL)) {
		INIT_LIST_HEAD(&stream->td_list);
		INIT_LIST_HEAD(&stream->free_list);
		stream->next_uframe = -1;
	}
	return stream;
}