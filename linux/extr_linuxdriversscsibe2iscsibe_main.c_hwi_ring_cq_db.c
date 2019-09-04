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
typedef  int u32 ;
struct beiscsi_hba {scalar_t__ db_va; } ;

/* Variables and functions */
 unsigned int DB_CQ_HIGH_FEILD_SHIFT ; 
 unsigned int DB_CQ_HIGH_SET_SHIFT ; 
 unsigned int DB_CQ_NUM_POPPED_SHIFT ; 
 scalar_t__ DB_CQ_OFFSET ; 
 int DB_CQ_REARM_SHIFT ; 
 unsigned int DB_CQ_RING_ID_HIGH_MASK ; 
 unsigned int DB_CQ_RING_ID_LOW_MASK ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

void hwi_ring_cq_db(struct beiscsi_hba *phba,
			   unsigned int id, unsigned int num_processed,
			   unsigned char rearm)
{
	u32 val = 0;

	if (rearm)
		val |= 1 << DB_CQ_REARM_SHIFT;

	val |= num_processed << DB_CQ_NUM_POPPED_SHIFT;

	/* Setting lower order CQ_ID Bits */
	val |= (id & DB_CQ_RING_ID_LOW_MASK);

	/* Setting Higher order CQ_ID Bits */
	val |= (((id >> DB_CQ_HIGH_FEILD_SHIFT) &
		  DB_CQ_RING_ID_HIGH_MASK)
		  << DB_CQ_HIGH_SET_SHIFT);

	iowrite32(val, phba->db_va + DB_CQ_OFFSET);
}