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
typedef  scalar_t__ const u32 ;
typedef  int /*<<< orphan*/  cid ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__ const*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
#define  VMADDR_CID_RESERVED 128 

__attribute__((used)) static bool vmci_transport_stream_allow(u32 cid, u32 port)
{
	static const u32 non_socket_contexts[] = {
		VMADDR_CID_RESERVED,
	};
	int i;

	BUILD_BUG_ON(sizeof(cid) != sizeof(*non_socket_contexts));

	for (i = 0; i < ARRAY_SIZE(non_socket_contexts); i++) {
		if (cid == non_socket_contexts[i])
			return false;
	}

	return true;
}