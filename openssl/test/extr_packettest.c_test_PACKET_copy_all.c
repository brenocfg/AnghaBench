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
 int /*<<< orphan*/  PACKET_copy_all (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbuf ; 

__attribute__((used)) static int test_PACKET_copy_all(void)
{
    unsigned char tmp[BUF_LEN];
    PACKET pkt;
    size_t len;

    if (!TEST_true(PACKET_buf_init(&pkt, smbuf, BUF_LEN))
            || !TEST_true(PACKET_copy_all(&pkt, tmp, BUF_LEN, &len))
            || !TEST_size_t_eq(len, BUF_LEN)
            || !TEST_mem_eq(smbuf, BUF_LEN, tmp, BUF_LEN)
            || !TEST_size_t_eq(PACKET_remaining(&pkt), BUF_LEN)
            || !TEST_false(PACKET_copy_all(&pkt, tmp, BUF_LEN - 1, &len)))
        return 0;

    return 1;
}