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

/* Variables and functions */
 int SNIC_TGT_STAT_DEL ; 
 int SNIC_TGT_STAT_INIT ; 
 char const** snic_tgt_state_str ; 

const char *
snic_tgt_state_to_str(int state)
{
	return ((state >= SNIC_TGT_STAT_INIT && state <= SNIC_TGT_STAT_DEL) ?
		snic_tgt_state_str[state] : "UNKNOWN");
}