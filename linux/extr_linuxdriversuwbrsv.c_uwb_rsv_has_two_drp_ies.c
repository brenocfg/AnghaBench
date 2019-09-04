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

bool uwb_rsv_has_two_drp_ies(struct uwb_rsv *rsv)
{
	static const bool has_two_drp_ies[] = {
		[UWB_RSV_STATE_O_INITIATED]               = false,
		[UWB_RSV_STATE_O_PENDING]                 = false,
		[UWB_RSV_STATE_O_MODIFIED]                = false,
		[UWB_RSV_STATE_O_ESTABLISHED]             = false,
		[UWB_RSV_STATE_O_TO_BE_MOVED]             = false,
		[UWB_RSV_STATE_O_MOVE_COMBINING]          = false,
		[UWB_RSV_STATE_O_MOVE_REDUCING]           = false,
		[UWB_RSV_STATE_O_MOVE_EXPANDING]          = true,
		[UWB_RSV_STATE_T_ACCEPTED]                = false,
		[UWB_RSV_STATE_T_CONFLICT]                = false,
		[UWB_RSV_STATE_T_PENDING]                 = false,
		[UWB_RSV_STATE_T_DENIED]                  = false,
		[UWB_RSV_STATE_T_RESIZED]                 = false,
		[UWB_RSV_STATE_T_EXPANDING_ACCEPTED]      = true,
		[UWB_RSV_STATE_T_EXPANDING_CONFLICT]      = true,
		[UWB_RSV_STATE_T_EXPANDING_PENDING]       = true,
		[UWB_RSV_STATE_T_EXPANDING_DENIED]        = true,
	};

	return has_two_drp_ies[rsv->state];
}