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
typedef  int /*<<< orphan*/  WPACKET ;

/* Variables and functions */
 int WPACKET_start_sub_packet_len__ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int WPACKET_start_sub_packet(WPACKET *pkt)
{
    return WPACKET_start_sub_packet_len__(pkt, 0);
}