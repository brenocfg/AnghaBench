#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  prev_size; } ;
struct free_block {scalar_t__ size; TYPE_1__ header; struct free_block* next; } ;
struct block_header {int dummy; } ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 TYPE_2__* AS_BLOCK_HEADER (struct free_block*,scalar_t__) ; 
 int /*<<< orphan*/  SLJIT_ASSERT (int) ; 
 int /*<<< orphan*/  allocator_grab_lock () ; 
 int /*<<< orphan*/  allocator_release_lock () ; 
 struct free_block* free_blocks ; 
 int /*<<< orphan*/  free_chunk (struct free_block*,scalar_t__) ; 
 int /*<<< orphan*/  sljit_remove_free_block (struct free_block*) ; 
 scalar_t__ total_size ; 

void sljit_free_unused_memory_exec(void)
{
	struct free_block* free_block;
	struct free_block* next_free_block;

	allocator_grab_lock();

	free_block = free_blocks;
	while (free_block) {
		next_free_block = free_block->next;
		if (!free_block->header.prev_size && 
				AS_BLOCK_HEADER(free_block, free_block->size)->size == 1) {
			total_size -= free_block->size;
			sljit_remove_free_block(free_block);
			free_chunk(free_block, free_block->size + sizeof(struct block_header));
		}
		free_block = next_free_block;
	}

	SLJIT_ASSERT((total_size && free_blocks) || (!total_size && !free_blocks));
	allocator_release_lock();
}