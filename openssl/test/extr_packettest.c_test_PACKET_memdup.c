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
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_memdup (int /*<<< orphan*/ *,unsigned char**,size_t*) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,scalar_t__) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbuf ; 

__attribute__((used)) static int test_PACKET_memdup(void)
{
    unsigned char *data = NULL;
    size_t len;
    PACKET pkt;
    int result = 0;

    if (!TEST_true(PACKET_buf_init(&pkt, smbuf, BUF_LEN))
            || !TEST_true(PACKET_memdup(&pkt, &data, &len))
            || !TEST_size_t_eq(len, BUF_LEN)
            || !TEST_mem_eq(data, len, PACKET_data(&pkt), len)
            || !TEST_true(PACKET_forward(&pkt, 10))
            || !TEST_true(PACKET_memdup(&pkt, &data, &len))
            || !TEST_size_t_eq(len, BUF_LEN - 10)
            || !TEST_mem_eq(data, len, PACKET_data(&pkt), len))
        goto end;
    result = 1;
end:
    OPENSSL_free(data);
    return result;
}