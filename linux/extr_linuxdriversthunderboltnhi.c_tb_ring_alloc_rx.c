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
typedef  int /*<<< orphan*/  u16 ;
struct tb_ring {int dummy; } ;
struct tb_nhi {int dummy; } ;

/* Variables and functions */
 struct tb_ring* tb_ring_alloc (struct tb_nhi*,int,int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*),void*) ; 

struct tb_ring *tb_ring_alloc_rx(struct tb_nhi *nhi, int hop, int size,
				 unsigned int flags, u16 sof_mask, u16 eof_mask,
				 void (*start_poll)(void *), void *poll_data)
{
	return tb_ring_alloc(nhi, hop, size, false, flags, sof_mask, eof_mask,
			     start_poll, poll_data);
}