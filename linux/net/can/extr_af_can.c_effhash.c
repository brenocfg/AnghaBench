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
typedef  unsigned int canid_t ;

/* Variables and functions */
 unsigned int CAN_EFF_RCV_HASH_BITS ; 

__attribute__((used)) static unsigned int effhash(canid_t can_id)
{
	unsigned int hash;

	hash = can_id;
	hash ^= can_id >> CAN_EFF_RCV_HASH_BITS;
	hash ^= can_id >> (2 * CAN_EFF_RCV_HASH_BITS);

	return hash & ((1 << CAN_EFF_RCV_HASH_BITS) - 1);
}