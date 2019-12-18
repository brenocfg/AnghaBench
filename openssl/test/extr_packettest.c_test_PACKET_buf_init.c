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
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_PACKET_buf_init(void)
{
    unsigned char buf1[BUF_LEN];
    PACKET pkt;

    /* Also tests PACKET_remaining() */
    if (!TEST_true(PACKET_buf_init(&pkt, buf1, 4))
            || !TEST_size_t_eq(PACKET_remaining(&pkt), 4)
            || !TEST_true(PACKET_buf_init(&pkt, buf1, BUF_LEN))
            || !TEST_size_t_eq(PACKET_remaining(&pkt), BUF_LEN)
            || !TEST_false(PACKET_buf_init(&pkt, buf1, -1)))
        return 0;

    return 1;
}