#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sound_queue {int locked; scalar_t__ user_frags; scalar_t__ max_count; scalar_t__ numBufs; scalar_t__ max_active; int block_size; int bufSize; int user_frag_size; int rear; scalar_t__ active; scalar_t__ syncing; scalar_t__ rear_size; scalar_t__ count; scalar_t__ front; } ;
struct TYPE_7__ {int (* write_sq_setup ) () ;int /*<<< orphan*/  (* init ) () ;} ;
struct TYPE_6__ {int size; int stereo; int speed; } ;
struct TYPE_5__ {int size; int stereo; int speed; } ;
struct TYPE_8__ {TYPE_3__ mach; TYPE_2__ hard; TYPE_1__ soft; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_4__ dmasound ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  stub1 () ; 
 struct sound_queue write_sq ; 

__attribute__((used)) static int sq_setup(struct sound_queue *sq)
{
	int (*setup_func)(void) = NULL;
	int hard_frame ;

	if (sq->locked) { /* are we already set? - and not changeable */
#ifdef DEBUG_DMASOUND
printk("dmasound_core: tried to sq_setup a locked queue\n") ;
#endif
		return -EINVAL ;
	}
	sq->locked = 1 ; /* don't think we have a race prob. here _check_ */

	/* make sure that the parameters are set up
	   This should have been done already...
	*/

	dmasound.mach.init();

	/* OK.  If the user has set fragment parameters explicitly, then we
	   should leave them alone... as long as they are valid.
	   Invalid user fragment params can occur if we allow the whole buffer
	   to be used when the user requests the fragments sizes (with no soft
	   x-lation) and then the user subsequently sets a soft x-lation that
	   requires increased internal buffering.

	   Othwerwise (if the user did not set them) OSS says that we should
	   select frag params on the basis of 0.5 s output & 0.1 s input
	   latency. (TODO.  For now we will copy in the defaults.)
	*/

	if (sq->user_frags <= 0) {
		sq->max_count = sq->numBufs ;
		sq->max_active = sq->numBufs ;
		sq->block_size = sq->bufSize;
		/* set up the user info */
		sq->user_frags = sq->numBufs ;
		sq->user_frag_size = sq->bufSize ;
		sq->user_frag_size *=
			(dmasound.soft.size * (dmasound.soft.stereo+1) ) ;
		sq->user_frag_size /=
			(dmasound.hard.size * (dmasound.hard.stereo+1) ) ;
	} else {
		/* work out requested block size */
		sq->block_size = sq->user_frag_size ;
		sq->block_size *=
			(dmasound.hard.size * (dmasound.hard.stereo+1) ) ;
		sq->block_size /=
			(dmasound.soft.size * (dmasound.soft.stereo+1) ) ;
		/* the user wants to write frag-size chunks */
		sq->block_size *= dmasound.hard.speed ;
		sq->block_size /= dmasound.soft.speed ;
		/* this only works for size values which are powers of 2 */
		hard_frame =
			(dmasound.hard.size * (dmasound.hard.stereo+1))/8 ;
		sq->block_size +=  (hard_frame - 1) ;
		sq->block_size &= ~(hard_frame - 1) ; /* make sure we are aligned */
		/* let's just check for obvious mistakes */
		if ( sq->block_size <= 0 || sq->block_size > sq->bufSize) {
#ifdef DEBUG_DMASOUND
printk("dmasound_core: invalid frag size (user set %d)\n", sq->user_frag_size) ;
#endif
			sq->block_size = sq->bufSize ;
		}
		if ( sq->user_frags <= sq->numBufs ) {
			sq->max_count = sq->user_frags ;
			/* if user has set max_active - then use it */
			sq->max_active = (sq->max_active <= sq->max_count) ?
				sq->max_active : sq->max_count ;
		} else {
#ifdef DEBUG_DMASOUND
printk("dmasound_core: invalid frag count (user set %d)\n", sq->user_frags) ;
#endif
			sq->max_count =
			sq->max_active = sq->numBufs ;
		}
	}
	sq->front = sq->count = sq->rear_size = 0;
	sq->syncing = 0;
	sq->active = 0;

	if (sq == &write_sq) {
	    sq->rear = -1;
	    setup_func = dmasound.mach.write_sq_setup;
	}
	if (setup_func)
	    return setup_func();
	return 0 ;
}