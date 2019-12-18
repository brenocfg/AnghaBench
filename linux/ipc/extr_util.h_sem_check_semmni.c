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
struct ipc_namespace {scalar_t__* sem_ctls; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ ipc_mni ; 

__attribute__((used)) static inline int sem_check_semmni(struct ipc_namespace *ns) {
	/*
	 * Check semmni range [0, ipc_mni]
	 * semmni is the last element of sem_ctls[4] array
	 */
	return ((ns->sem_ctls[3] < 0) || (ns->sem_ctls[3] > ipc_mni))
		? -ERANGE : 0;
}