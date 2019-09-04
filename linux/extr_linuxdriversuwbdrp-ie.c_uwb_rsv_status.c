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
struct uwb_rsv {size_t state; } ;

/* Variables and functions */
#define  UWB_RSV_STATE_O_ESTABLISHED 144 
#define  UWB_RSV_STATE_O_INITIATED 143 
#define  UWB_RSV_STATE_O_MODIFIED 142 
#define  UWB_RSV_STATE_O_MOVE_COMBINING 141 
#define  UWB_RSV_STATE_O_MOVE_EXPANDING 140 
#define  UWB_RSV_STATE_O_MOVE_REDUCING 139 
#define  UWB_RSV_STATE_O_PENDING 138 
#define  UWB_RSV_STATE_O_TO_BE_MOVED 137 
#define  UWB_RSV_STATE_T_ACCEPTED 136 
#define  UWB_RSV_STATE_T_CONFLICT 135 
#define  UWB_RSV_STATE_T_DENIED 134 
#define  UWB_RSV_STATE_T_EXPANDING_ACCEPTED 133 
#define  UWB_RSV_STATE_T_EXPANDING_CONFLICT 132 
#define  UWB_RSV_STATE_T_EXPANDING_DENIED 131 
#define  UWB_RSV_STATE_T_EXPANDING_PENDING 130 
#define  UWB_RSV_STATE_T_PENDING 129 
#define  UWB_RSV_STATE_T_RESIZED 128 

int uwb_rsv_status(struct uwb_rsv *rsv)
{
	static const int statuses[] = {
		[UWB_RSV_STATE_O_INITIATED]          = 0,
		[UWB_RSV_STATE_O_PENDING]            = 0,
		[UWB_RSV_STATE_O_MODIFIED]           = 1,
		[UWB_RSV_STATE_O_ESTABLISHED]        = 1,
		[UWB_RSV_STATE_O_TO_BE_MOVED]        = 0,
		[UWB_RSV_STATE_O_MOVE_COMBINING]     = 1,
		[UWB_RSV_STATE_O_MOVE_REDUCING]      = 1,
		[UWB_RSV_STATE_O_MOVE_EXPANDING]     = 1,
		[UWB_RSV_STATE_T_ACCEPTED]           = 1,
		[UWB_RSV_STATE_T_CONFLICT]           = 0,
		[UWB_RSV_STATE_T_PENDING]            = 0,
		[UWB_RSV_STATE_T_DENIED]             = 0,
		[UWB_RSV_STATE_T_RESIZED]            = 1,
		[UWB_RSV_STATE_T_EXPANDING_ACCEPTED] = 1,
		[UWB_RSV_STATE_T_EXPANDING_CONFLICT] = 1,
		[UWB_RSV_STATE_T_EXPANDING_PENDING]  = 1,
		[UWB_RSV_STATE_T_EXPANDING_DENIED]   = 1,

	};

	return statuses[rsv->state];
}