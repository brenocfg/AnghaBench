#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct airo_info {int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {int window; int rx; } ;
typedef  TYPE_1__ miccntx ;

/* Variables and functions */
 int ERROR ; 
 int /*<<< orphan*/  FLAG_UPDATE_MULTI ; 
 int /*<<< orphan*/  FLAG_UPDATE_UNI ; 
 int /*<<< orphan*/  MoveWindow (TYPE_1__*,int) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int RxSeqValid (struct airo_info *ai,miccntx *context,int mcast,u32 micSeq)
{
	u32 seq,index;

	//Allow for the ap being rebooted - if it is then use the next 
	//sequence number of the current sequence number - might go backwards

	if (mcast) {
		if (test_bit(FLAG_UPDATE_MULTI, &ai->flags)) {
			clear_bit (FLAG_UPDATE_MULTI, &ai->flags);
			context->window = (micSeq > 33) ? micSeq : 33;
			context->rx     = 0;        // Reset rx
		}
	} else if (test_bit(FLAG_UPDATE_UNI, &ai->flags)) {
		clear_bit (FLAG_UPDATE_UNI, &ai->flags);
		context->window = (micSeq > 33) ? micSeq : 33; // Move window
		context->rx     = 0;        // Reset rx
	}

	//Make sequence number relative to START of window
	seq = micSeq - (context->window - 33);

	//Too old of a SEQ number to check.
	if ((s32)seq < 0)
		return ERROR;
    
	if ( seq > 64 ) {
		//Window is infinite forward
		MoveWindow(context,micSeq);
		return SUCCESS;
	}

	// We are in the window. Now check the context rx bit to see if it was already sent
	seq >>= 1;         //divide by 2 because we only have odd numbers
	index = 1 << seq;  //Get an index number

	if (!(context->rx & index)) {
		//micSEQ falls inside the window.
		//Add seqence number to the list of received numbers.
		context->rx |= index;

		MoveWindow(context,micSeq);

		return SUCCESS;
	}
	return ERROR;
}