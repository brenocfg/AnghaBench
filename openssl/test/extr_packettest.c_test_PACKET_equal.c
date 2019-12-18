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
 int BUF_LEN ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  PACKET_equal (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 scalar_t__ smbuf ; 

__attribute__((used)) static int test_PACKET_equal(void)
{
    PACKET pkt;

    if (!TEST_true(PACKET_buf_init(&pkt, smbuf, 4))
            || !TEST_true(PACKET_equal(&pkt, smbuf, 4))
            || !TEST_false(PACKET_equal(&pkt, smbuf + 1, 4))
            || !TEST_true(PACKET_buf_init(&pkt, smbuf, BUF_LEN))
            || !TEST_true(PACKET_equal(&pkt, smbuf, BUF_LEN))
            || !TEST_false(PACKET_equal(&pkt, smbuf, BUF_LEN - 1))
            || !TEST_false(PACKET_equal(&pkt, smbuf, BUF_LEN + 1))
            || !TEST_false(PACKET_equal(&pkt, smbuf, 0)))
        return 0;

    return 1;
}