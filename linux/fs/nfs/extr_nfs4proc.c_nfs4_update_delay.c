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
 long NFS4_POLL_RETRY_MAX ; 
 long NFS4_POLL_RETRY_MIN ; 

__attribute__((used)) static long nfs4_update_delay(long *timeout)
{
	long ret;
	if (!timeout)
		return NFS4_POLL_RETRY_MAX;
	if (*timeout <= 0)
		*timeout = NFS4_POLL_RETRY_MIN;
	if (*timeout > NFS4_POLL_RETRY_MAX)
		*timeout = NFS4_POLL_RETRY_MAX;
	ret = *timeout;
	*timeout <<= 1;
	return ret;
}