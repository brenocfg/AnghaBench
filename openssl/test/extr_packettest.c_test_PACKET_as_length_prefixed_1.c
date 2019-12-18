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
typedef  int /*<<< orphan*/  subpkt ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int BUF_LEN ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char*,size_t const) ; 
 int /*<<< orphan*/  PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_PACKET_as_length_prefixed_1(void)
{
    unsigned char buf1[BUF_LEN];
    const size_t len = 16;
    unsigned int i;
    PACKET pkt, exact_pkt, subpkt;

    memset(&subpkt, 0, sizeof(subpkt));
    buf1[0] = (unsigned char)len;
    for (i = 1; i < BUF_LEN; i++)
        buf1[i] = (i * 2) & 0xff;

    if (!TEST_true(PACKET_buf_init(&pkt, buf1, BUF_LEN))
            || !TEST_true(PACKET_buf_init(&exact_pkt, buf1, len + 1))
            || !TEST_false(PACKET_as_length_prefixed_1(&pkt, &subpkt))
            || !TEST_size_t_eq(PACKET_remaining(&pkt), BUF_LEN)
            || !TEST_true(PACKET_as_length_prefixed_1(&exact_pkt, &subpkt))
            || !TEST_size_t_eq(PACKET_remaining(&exact_pkt), 0)
            || !TEST_size_t_eq(PACKET_remaining(&subpkt), len))
        return 0;

    return 1;
}