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
 scalar_t__ VMADDR_CID_HYPERVISOR ; 
 scalar_t__ VMCI_UNITY_PBRPC_REGISTER ; 

__attribute__((used)) static bool vmci_transport_dgram_allow(u32 cid, u32 port)
{
	if (cid == VMADDR_CID_HYPERVISOR) {
		/* Registrations of PBRPC Servers do not modify VMX/Hypervisor
		 * state and are allowed.
		 */
		return port == VMCI_UNITY_PBRPC_REGISTER;
	}

	return true;
}