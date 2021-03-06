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
typedef  int u8 ;
struct sk_buff {int* data; } ;

/* Variables and functions */

__attribute__((used)) static u8 nfc_llcp_ptype(struct sk_buff *pdu)
{
	return ((pdu->data[0] & 0x03) << 2) | ((pdu->data[1] & 0xc0) >> 6);
}