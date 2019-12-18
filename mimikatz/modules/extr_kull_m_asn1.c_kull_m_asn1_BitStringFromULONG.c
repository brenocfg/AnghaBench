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
typedef  int /*<<< orphan*/  flagBuffer ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/  BerElement ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  _byteswap_ulong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

void kull_m_asn1_BitStringFromULONG(BerElement * pBer, ULONG data)
{
	BYTE flagBuffer[5] = {0};
	*(PDWORD) (flagBuffer + 1) = _byteswap_ulong(data);
	ber_printf(pBer, "X", flagBuffer, sizeof(flagBuffer));
}