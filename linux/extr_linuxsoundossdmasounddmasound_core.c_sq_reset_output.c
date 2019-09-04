#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rear; scalar_t__ user_frag_size; scalar_t__ user_frags; scalar_t__ locked; scalar_t__ front; scalar_t__ rear_size; scalar_t__ count; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  sound_silence () ; 
 TYPE_1__ write_sq ; 

__attribute__((used)) static void sq_reset_output(void)
{
	sound_silence(); /* this _must_ stop DMA, we might be about to lose the buffers */
	write_sq.active = 0;
	write_sq.count = 0;
	write_sq.rear_size = 0;
	/* write_sq.front = (write_sq.rear+1) % write_sq.max_count;*/
	write_sq.front = 0 ;
	write_sq.rear = -1 ; /* same as for set-up */

	/* OK - we can unlock the parameters and fragment settings */
	write_sq.locked = 0 ;
	write_sq.user_frags = 0 ;
	write_sq.user_frag_size = 0 ;
}