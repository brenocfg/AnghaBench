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
struct TYPE_5__ {int blocks_in_use; int /*<<< orphan*/  allocation_table; } ;
typedef  TYPE_1__ urlcache_header ;
struct TYPE_6__ {int blocks_used; } ;
typedef  TYPE_2__ entry_header ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BLOCKSIZE ; 
 int ENTRY_START_OFFSET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  urlcache_block_free (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL urlcache_entry_free(urlcache_header *header, entry_header *entry)
{
    DWORD start_block, block;

    /* update allocation table */
    start_block = ((DWORD)((BYTE*)entry - (BYTE*)header) - ENTRY_START_OFFSET) / BLOCKSIZE;
    for(block = start_block; block < start_block+entry->blocks_used; block++)
        urlcache_block_free(header->allocation_table, block);

    header->blocks_in_use -= entry->blocks_used;
    return TRUE;
}