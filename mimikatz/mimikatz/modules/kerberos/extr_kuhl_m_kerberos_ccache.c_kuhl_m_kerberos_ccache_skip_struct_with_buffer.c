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
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ _byteswap_ulong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ccache_skip_buffer (scalar_t__*) ; 

void kuhl_m_kerberos_ccache_skip_struct_with_buffer(PBYTE *data)
{
	DWORD i, numBuff = _byteswap_ulong(*(PDWORD) *data); *data += sizeof(DWORD);
	for (i = 0; i < numBuff; i++)
	{
		*data += sizeof(USHORT);
		kuhl_m_kerberos_ccache_skip_buffer(data);
	}
}