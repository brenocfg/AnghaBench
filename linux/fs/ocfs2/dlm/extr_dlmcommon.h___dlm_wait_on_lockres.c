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
struct dlm_lock_resource {int dummy; } ;

/* Variables and functions */
 int DLM_LOCK_RES_IN_PROGRESS ; 
 int DLM_LOCK_RES_MIGRATING ; 
 int DLM_LOCK_RES_RECOVERING ; 
 int DLM_LOCK_RES_RECOVERY_WAITING ; 
 int /*<<< orphan*/  __dlm_wait_on_lockres_flags (struct dlm_lock_resource*,int) ; 

__attribute__((used)) static inline void __dlm_wait_on_lockres(struct dlm_lock_resource *res)
{
	__dlm_wait_on_lockres_flags(res, (DLM_LOCK_RES_IN_PROGRESS|
				    	  DLM_LOCK_RES_RECOVERING|
					  DLM_LOCK_RES_RECOVERY_WAITING|
					  DLM_LOCK_RES_MIGRATING));
}