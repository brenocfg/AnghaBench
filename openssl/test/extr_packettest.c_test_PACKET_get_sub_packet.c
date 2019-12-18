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
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 scalar_t__ BUF_LEN ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_get_net_4 (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  PACKET_get_sub_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ulong_eq (unsigned long,int) ; 
 int /*<<< orphan*/  smbuf ; 

__attribute__((used)) static int test_PACKET_get_sub_packet(void)
{
    PACKET pkt, subpkt;
    unsigned long i = 0;

    if (!TEST_true(PACKET_buf_init(&pkt, smbuf, BUF_LEN))
            || !TEST_true(PACKET_get_sub_packet(&pkt, &subpkt, 4))
            || !TEST_true(PACKET_get_net_4(&subpkt, &i))
            || !TEST_ulong_eq(i, 0x02040608UL)
            || !TEST_size_t_eq(PACKET_remaining(&subpkt), 0)
            || !TEST_true(PACKET_forward(&pkt, BUF_LEN - 8))
            || !TEST_true(PACKET_get_sub_packet(&pkt, &subpkt, 4))
            || !TEST_true(PACKET_get_net_4(&subpkt, &i))
            || !TEST_ulong_eq(i, 0xf8fafcfeUL)
            || !TEST_size_t_eq(PACKET_remaining(&subpkt), 0)
            || !TEST_false(PACKET_get_sub_packet(&pkt, &subpkt, 4)))
        return 0;

    return 1;
}