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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
#define  DCCPF_ACK_RATIO 129 
 int /*<<< orphan*/  DCCPF_ACK_RATIO_MAX ; 
#define  DCCPF_SEQUENCE_WINDOW 128 
 int /*<<< orphan*/  DCCPF_SEQ_WMAX ; 
 int /*<<< orphan*/  DCCPF_SEQ_WMIN ; 

__attribute__((used)) static u8 dccp_feat_is_valid_nn_val(u8 feat_num, u64 val)
{
	switch (feat_num) {
	case DCCPF_ACK_RATIO:
		return val <= DCCPF_ACK_RATIO_MAX;
	case DCCPF_SEQUENCE_WINDOW:
		return val >= DCCPF_SEQ_WMIN && val <= DCCPF_SEQ_WMAX;
	}
	return 0;	/* feature unknown - so we can't tell */
}