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
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char*,size_t const) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_eq (unsigned int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_PACKET_get_length_prefixed_1(void)
{
    unsigned char buf1[BUF_LEN];
    const size_t len = 16;
    unsigned int i;
    PACKET pkt, short_pkt, subpkt;

    memset(&subpkt, 0, sizeof(subpkt));
    buf1[0] = (unsigned char)len;
    for (i = 1; i < BUF_LEN; i++)
        buf1[i] = (i * 2) & 0xff;

    if (!TEST_true(PACKET_buf_init(&pkt, buf1, BUF_LEN))
            || !TEST_true(PACKET_buf_init(&short_pkt, buf1, len))
            || !TEST_true(PACKET_get_length_prefixed_1(&pkt, &subpkt))
            || !TEST_size_t_eq(PACKET_remaining(&subpkt), len)
            || !TEST_true(PACKET_get_net_2(&subpkt, &i))
            || !TEST_uint_eq(i, 0x0204)
            || !TEST_false(PACKET_get_length_prefixed_1(&short_pkt, &subpkt))
            || !TEST_size_t_eq(PACKET_remaining(&short_pkt), len))
        return 0;

    return 1;
}