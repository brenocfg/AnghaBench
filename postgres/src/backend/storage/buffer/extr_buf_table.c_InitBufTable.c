#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int keysize; int entrysize; int /*<<< orphan*/  num_partitions; } ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  BufferTag ;
typedef  int /*<<< orphan*/  BufferLookupEnt ;

/* Variables and functions */
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int HASH_PARTITION ; 
 int /*<<< orphan*/  NUM_BUFFER_PARTITIONS ; 
 int /*<<< orphan*/  SharedBufHash ; 
 int /*<<< orphan*/  ShmemInitHash (char*,int,int,TYPE_1__*,int) ; 

void
InitBufTable(int size)
{
	HASHCTL		info;

	/* assume no locking is needed yet */

	/* BufferTag maps to Buffer */
	info.keysize = sizeof(BufferTag);
	info.entrysize = sizeof(BufferLookupEnt);
	info.num_partitions = NUM_BUFFER_PARTITIONS;

	SharedBufHash = ShmemInitHash("Shared Buffer Lookup Table",
								  size, size,
								  &info,
								  HASH_ELEM | HASH_BLOBS | HASH_PARTITION);
}