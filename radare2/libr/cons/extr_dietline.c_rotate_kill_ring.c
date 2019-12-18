#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t index; scalar_t__* data; } ;
struct TYPE_6__ {scalar_t__ kill_ring_ptr; TYPE_2__* kill_ring; int /*<<< orphan*/  clipboard; TYPE_1__ buffer; } ;
struct TYPE_5__ {scalar_t__ length; } ;

/* Variables and functions */
 TYPE_3__ I ; 
 scalar_t__ enable_yank_pop ; 
 int /*<<< orphan*/  paste () ; 
 int /*<<< orphan*/  r_list_get_n (TYPE_2__*,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rotate_kill_ring() {
	if (enable_yank_pop) {
		I.buffer.index -= strlen (r_list_get_n (I.kill_ring, I.kill_ring_ptr));
		I.buffer.data[I.buffer.index] = 0;
		I.kill_ring_ptr -= 1;
		if (I.kill_ring_ptr < 0) {
			I.kill_ring_ptr = I.kill_ring->length - 1;
		}
		I.clipboard = r_list_get_n (I.kill_ring, I.kill_ring_ptr);
		paste ();
	}
}