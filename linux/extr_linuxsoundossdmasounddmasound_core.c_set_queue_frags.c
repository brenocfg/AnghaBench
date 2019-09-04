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
struct sound_queue {int bufSize; int numBufs; int user_frags; int max_active; int user_frag_size; scalar_t__ locked; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_FRAG_SIZE ; 
 int MIN_FRAG_SIZE ; 

__attribute__((used)) static int set_queue_frags(struct sound_queue *sq, int bufs, int size)
{
	if (sq->locked) {
#ifdef DEBUG_DMASOUND
printk("dmasound_core: tried to set_queue_frags on a locked queue\n") ;
#endif
		return -EINVAL ;
	}

	if ((size < MIN_FRAG_SIZE) || (size > MAX_FRAG_SIZE))
		return -EINVAL ;
	size = (1<<size) ; /* now in bytes */
	if (size > sq->bufSize)
		return -EINVAL ; /* this might still not work */

	if (bufs <= 0)
		return -EINVAL ;
	if (bufs > sq->numBufs) /* the user is allowed say "don't care" with 0x7fff */
		bufs = sq->numBufs ;

	/* there is, currently, no way to specify max_active separately
	   from max_count.  This could be a LL driver issue - I guess
	   if there is a requirement for these values to be different then
	  we will have to pass that info. up to this level.
	*/
	sq->user_frags =
	sq->max_active = bufs ;
	sq->user_frag_size = size ;

	return 0 ;
}