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

/* Variables and functions */
 size_t MWIFIEX_COALESCE_MAX_BYTESEQ ; 
 int PACKET_TYPE_BROADCAST ; 
 int PACKET_TYPE_MULTICAST ; 
 int PACKET_TYPE_UNICAST ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 

__attribute__((used)) static int mwifiex_get_coalesce_pkt_type(u8 *byte_seq)
{
	static const u8 ipv4_mc_mac[] = {0x33, 0x33};
	static const u8 ipv6_mc_mac[] = {0x01, 0x00, 0x5e};
	static const u8 bc_mac[] = {0xff, 0xff, 0xff, 0xff};

	if ((byte_seq[0] & 0x01) &&
	    (byte_seq[MWIFIEX_COALESCE_MAX_BYTESEQ] == 1))
		return PACKET_TYPE_UNICAST;
	else if (!memcmp(byte_seq, bc_mac, 4))
		return PACKET_TYPE_BROADCAST;
	else if ((!memcmp(byte_seq, ipv4_mc_mac, 2) &&
		  byte_seq[MWIFIEX_COALESCE_MAX_BYTESEQ] == 2) ||
		 (!memcmp(byte_seq, ipv6_mc_mac, 3) &&
		  byte_seq[MWIFIEX_COALESCE_MAX_BYTESEQ] == 3))
		return PACKET_TYPE_MULTICAST;

	return 0;
}