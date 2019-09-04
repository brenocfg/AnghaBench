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
 int /*<<< orphan*/  PACKET_get_net_3 (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ulong_eq (unsigned long,int) ; 
 int /*<<< orphan*/  smbuf ; 

__attribute__((used)) static int test_PACKET_get_net_3(void)
{
    unsigned long i = 0;
    PACKET pkt;

    if (!TEST_true(PACKET_buf_init(&pkt, smbuf, BUF_LEN))
            || !TEST_true(PACKET_get_net_3(&pkt, &i))
            || !TEST_ulong_eq(i, 0x020406UL)
            || !TEST_true(PACKET_forward(&pkt, BUF_LEN - 6))
            || !TEST_true(PACKET_get_net_3(&pkt, &i))
            || !TEST_ulong_eq(i, 0xfafcfeUL)
            || !TEST_false(PACKET_get_net_3(&pkt, &i)))
        return 0;

    return 1;
}