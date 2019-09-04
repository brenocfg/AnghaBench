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
 scalar_t__ SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION ; 
 scalar_t__ SLIM_MSG_MC_REQUEST_INFORMATION ; 
 scalar_t__ SLIM_MSG_MC_REQUEST_VALUE ; 
 scalar_t__ SLIM_MSG_MT_CORE ; 

__attribute__((used)) static inline bool slim_tid_txn(u8 mt, u8 mc)
{
	return (mt == SLIM_MSG_MT_CORE &&
		(mc == SLIM_MSG_MC_REQUEST_INFORMATION ||
		 mc == SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION ||
		 mc == SLIM_MSG_MC_REQUEST_VALUE ||
		 mc == SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION));
}