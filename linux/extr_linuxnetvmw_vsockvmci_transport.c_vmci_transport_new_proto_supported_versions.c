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
typedef  int u16 ;

/* Variables and functions */
 int PROTOCOL_OVERRIDE ; 
 int VSOCK_PROTO_ALL_SUPPORTED ; 

__attribute__((used)) static u16 vmci_transport_new_proto_supported_versions(void)
{
	if (PROTOCOL_OVERRIDE != -1)
		return PROTOCOL_OVERRIDE;

	return VSOCK_PROTO_ALL_SUPPORTED;
}