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
typedef  void* u16 ;
struct qedi_portid_tbl {int /*<<< orphan*/  table; int /*<<< orphan*/  lock; void* next; void* max; void* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedi_init_id_tbl(struct qedi_portid_tbl *id_tbl, u16 size,
			    u16 start_id, u16 next)
{
	id_tbl->start = start_id;
	id_tbl->max = size;
	id_tbl->next = next;
	spin_lock_init(&id_tbl->lock);
	id_tbl->table = kcalloc(BITS_TO_LONGS(size), sizeof(long), GFP_KERNEL);
	if (!id_tbl->table)
		return -ENOMEM;

	return 0;
}