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
typedef  int /*<<< orphan*/ * MPT_CALLBACK ;

/* Variables and functions */
 int MPT_MAX_CALLBACKS ; 
 int /*<<< orphan*/ ** mpt_callbacks ; 

u8
mpt3sas_base_register_callback_handler(MPT_CALLBACK cb_func)
{
	u8 cb_idx;

	for (cb_idx = MPT_MAX_CALLBACKS-1; cb_idx; cb_idx--)
		if (mpt_callbacks[cb_idx] == NULL)
			break;

	mpt_callbacks[cb_idx] = cb_func;
	return cb_idx;
}