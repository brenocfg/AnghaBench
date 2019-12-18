#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_17__ {int /*<<< orphan*/ * leftmost; } ;
struct TYPE_13__ {int /*<<< orphan*/  uncompressed_base; int /*<<< orphan*/  compressed_base; } ;
struct TYPE_14__ {int record_count; TYPE_7__ groups; int /*<<< orphan*/  stream_padding; int /*<<< orphan*/  stream_flags; int /*<<< orphan*/  index_list_size; int /*<<< orphan*/  block_number_base; int /*<<< orphan*/  number; TYPE_1__ node; } ;
typedef  TYPE_2__ index_stream ;
typedef  int /*<<< orphan*/  index_record ;
struct TYPE_16__ {scalar_t__ compressed_base; scalar_t__ uncompressed_base; } ;
struct TYPE_15__ {int number_base; int allocated; int last; TYPE_6__ node; scalar_t__ records; } ;
typedef  TYPE_3__ index_group ;

/* Variables and functions */
 int PREALLOC_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  index_stream_end (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* index_stream_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_tree_append (TYPE_7__*,TYPE_6__*) ; 
 TYPE_3__* index_tree_next (TYPE_6__*) ; 
 TYPE_3__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static index_stream *
index_dup_stream(const index_stream *src, lzma_allocator *allocator)
{
	// Catch a somewhat theoretical integer overflow.
	if (src->record_count > PREALLOC_MAX)
		return NULL;

	// Allocate and initialize a new Stream.
	index_stream *dest = index_stream_init(src->node.compressed_base,
			src->node.uncompressed_base, src->number,
			src->block_number_base, allocator);

	// Return immediately if allocation failed or if there are
	// no groups to duplicate.
	if (dest == NULL || src->groups.leftmost == NULL)
		return dest;

	// Copy the overall information.
	dest->record_count = src->record_count;
	dest->index_list_size = src->index_list_size;
	dest->stream_flags = src->stream_flags;
	dest->stream_padding = src->stream_padding;

	// Allocate memory for the Records. We put all the Records into
	// a single group. It's simplest and also tends to make
	// lzma_index_locate() a little bit faster with very big Indexes.
	index_group *destg = lzma_alloc(sizeof(index_group)
			+ src->record_count * sizeof(index_record),
			allocator);
	if (destg == NULL) {
		index_stream_end(dest, allocator);
		return NULL;
	}

	// Initialize destg.
	destg->node.uncompressed_base = 0;
	destg->node.compressed_base = 0;
	destg->number_base = 1;
	destg->allocated = src->record_count;
	destg->last = src->record_count - 1;

	// Go through all the groups in src and copy the Records into destg.
	const index_group *srcg = (const index_group *)(src->groups.leftmost);
	size_t i = 0;
	do {
		memcpy(destg->records + i, srcg->records,
				(srcg->last + 1) * sizeof(index_record));
		i += srcg->last + 1;
		srcg = index_tree_next(&srcg->node);
	} while (srcg != NULL);

	assert(i == destg->allocated);

	// Add the group to the new Stream.
	index_tree_append(&dest->groups, &destg->node);

	return dest;
}