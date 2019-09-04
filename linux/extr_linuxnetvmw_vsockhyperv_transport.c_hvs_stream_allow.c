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
 scalar_t__ MAX_HOST_LISTEN_PORT ; 
 scalar_t__ VMADDR_CID_HOST ; 

__attribute__((used)) static bool hvs_stream_allow(u32 cid, u32 port)
{
	/* The host's port range [MIN_HOST_EPHEMERAL_PORT, 0xFFFFFFFF) is
	 * reserved as ephemeral ports, which are used as the host's ports
	 * when the host initiates connections.
	 *
	 * Perform this check in the guest so an immediate error is produced
	 * instead of a timeout.
	 */
	if (port > MAX_HOST_LISTEN_PORT)
		return false;

	if (cid == VMADDR_CID_HOST)
		return true;

	return false;
}