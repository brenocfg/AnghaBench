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
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_char_eq (unsigned char,int) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uchar_eq (unsigned char,int) ; 
 int /*<<< orphan*/  smbuf ; 

__attribute__((used)) static int test_PACKET_copy_bytes(void)
{
    unsigned char bytes[4];
    PACKET pkt;

    if (!TEST_true(PACKET_buf_init(&pkt, smbuf, BUF_LEN))
            || !TEST_true(PACKET_copy_bytes(&pkt, bytes, 4))
            || !TEST_char_eq(bytes[0], 2)
            || !TEST_char_eq(bytes[1], 4)
            || !TEST_char_eq(bytes[2], 6)
            || !TEST_char_eq(bytes[3], 8)
            || !TEST_size_t_eq(PACKET_remaining(&pkt), BUF_LEN - 4)
            || !TEST_true(PACKET_forward(&pkt, BUF_LEN - 8))
            || !TEST_true(PACKET_copy_bytes(&pkt, bytes, 4))
            || !TEST_uchar_eq(bytes[0], 0xf8)
            || !TEST_uchar_eq(bytes[1], 0xfa)
            || !TEST_uchar_eq(bytes[2], 0xfc)
            || !TEST_uchar_eq(bytes[3], 0xfe)
            || !TEST_false(PACKET_remaining(&pkt)))
        return 0;

    return 1;
}