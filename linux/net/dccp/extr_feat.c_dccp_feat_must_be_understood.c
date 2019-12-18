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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ DCCPF_CCID ; 
 scalar_t__ DCCPF_SEQUENCE_WINDOW ; 
 scalar_t__ DCCPF_SHORT_SEQNOS ; 

__attribute__((used)) static inline int dccp_feat_must_be_understood(u8 feat_num)
{
	return	feat_num == DCCPF_CCID || feat_num == DCCPF_SHORT_SEQNOS ||
		feat_num == DCCPF_SEQUENCE_WINDOW;
}