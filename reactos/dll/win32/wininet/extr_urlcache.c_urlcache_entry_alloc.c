#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ capacity_in_blocks; scalar_t__ blocks_in_use; int /*<<< orphan*/  allocation_table; } ;
typedef  TYPE_1__ urlcache_header ;
struct TYPE_6__ {scalar_t__ blocks_used; } ;
typedef  TYPE_2__ entry_header ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ BLOCKSIZE ; 
 int ENTRY_START_OFFSET ; 
 scalar_t__ ERROR_HANDLE_DISK_FULL ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  urlcache_block_alloc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ urlcache_block_is_free (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static DWORD urlcache_entry_alloc(urlcache_header *header, DWORD blocks_needed, entry_header **entry)
{
    DWORD block, block_size;

    for(block=0; block<header->capacity_in_blocks; block+=block_size+1)
    {
        block_size = 0;
        while(block_size<blocks_needed && block_size+block<header->capacity_in_blocks
                && urlcache_block_is_free(header->allocation_table, block+block_size))
            block_size++;

        if(block_size == blocks_needed)
        {
            DWORD index;

            TRACE("Found free blocks starting at no. %d (0x%x)\n", block, ENTRY_START_OFFSET+block*BLOCKSIZE);

            for(index=0; index<blocks_needed; index++)
                urlcache_block_alloc(header->allocation_table, block+index);

            *entry = (entry_header*)((BYTE*)header+ENTRY_START_OFFSET+block*BLOCKSIZE);
            for(index=0; index<blocks_needed*BLOCKSIZE/sizeof(DWORD); index++)
                ((DWORD*)*entry)[index] = 0xdeadbeef;
            (*entry)->blocks_used = blocks_needed;

            header->blocks_in_use += blocks_needed;
            return ERROR_SUCCESS;
        }
    }

    return ERROR_HANDLE_DISK_FULL;
}