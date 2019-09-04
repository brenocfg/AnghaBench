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
struct br_mdb_entry {unsigned char state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDB_FLAGS_OFFLOAD ; 
 unsigned char MDB_PG_FLAGS_OFFLOAD ; 
 unsigned char MDB_PG_FLAGS_PERMANENT ; 

__attribute__((used)) static void __mdb_entry_fill_flags(struct br_mdb_entry *e, unsigned char flags)
{
	e->state = flags & MDB_PG_FLAGS_PERMANENT;
	e->flags = 0;
	if (flags & MDB_PG_FLAGS_OFFLOAD)
		e->flags |= MDB_FLAGS_OFFLOAD;
}