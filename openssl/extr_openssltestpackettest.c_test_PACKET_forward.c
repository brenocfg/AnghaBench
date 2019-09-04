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
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_get_bytes (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uchar_eq (unsigned char const,int) ; 
 int /*<<< orphan*/  smbuf ; 

__attribute__((used)) static int test_PACKET_forward(void)
{
    const unsigned char *byte = NULL;
    PACKET pkt;

    if (!TEST_true(PACKET_buf_init(&pkt, smbuf, BUF_LEN))
            || !TEST_true(PACKET_forward(&pkt, 1))
            || !TEST_true(PACKET_get_bytes(&pkt, &byte, 1))
            || !TEST_uchar_eq(byte[0], 4)
            || !TEST_true(PACKET_forward(&pkt, BUF_LEN - 3))
            || !TEST_true(PACKET_get_bytes(&pkt, &byte, 1))
            || !TEST_uchar_eq(byte[0], 0xfe))
        return 0;

    return 1;
}