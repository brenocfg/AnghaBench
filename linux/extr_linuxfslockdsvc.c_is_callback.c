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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ NLMPROC_CANCEL_RES ; 
 scalar_t__ NLMPROC_GRANTED ; 
 scalar_t__ NLMPROC_GRANTED_MSG ; 
 scalar_t__ NLMPROC_LOCK_RES ; 
 scalar_t__ NLMPROC_NSM_NOTIFY ; 
 scalar_t__ NLMPROC_TEST_RES ; 
 scalar_t__ NLMPROC_UNLOCK_RES ; 

__attribute__((used)) static inline int is_callback(u32 proc)
{
	return proc == NLMPROC_GRANTED
		|| proc == NLMPROC_GRANTED_MSG
		|| proc == NLMPROC_TEST_RES
		|| proc == NLMPROC_LOCK_RES
		|| proc == NLMPROC_CANCEL_RES
		|| proc == NLMPROC_UNLOCK_RES
		|| proc == NLMPROC_NSM_NOTIFY;
}