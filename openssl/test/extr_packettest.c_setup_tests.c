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

/* Variables and functions */
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 unsigned int BUF_LEN ; 
 unsigned int* smbuf ; 
 int /*<<< orphan*/  test_PACKET_as_length_prefixed_1 ; 
 int /*<<< orphan*/  test_PACKET_as_length_prefixed_2 ; 
 int /*<<< orphan*/  test_PACKET_buf_init ; 
 int /*<<< orphan*/  test_PACKET_contains_zero_byte ; 
 int /*<<< orphan*/  test_PACKET_copy_all ; 
 int /*<<< orphan*/  test_PACKET_copy_bytes ; 
 int /*<<< orphan*/  test_PACKET_end ; 
 int /*<<< orphan*/  test_PACKET_equal ; 
 int /*<<< orphan*/  test_PACKET_forward ; 
 int /*<<< orphan*/  test_PACKET_get_1 ; 
 int /*<<< orphan*/  test_PACKET_get_4 ; 
 int /*<<< orphan*/  test_PACKET_get_bytes ; 
 int /*<<< orphan*/  test_PACKET_get_length_prefixed_1 ; 
 int /*<<< orphan*/  test_PACKET_get_length_prefixed_2 ; 
 int /*<<< orphan*/  test_PACKET_get_length_prefixed_3 ; 
 int /*<<< orphan*/  test_PACKET_get_net_2 ; 
 int /*<<< orphan*/  test_PACKET_get_net_3 ; 
 int /*<<< orphan*/  test_PACKET_get_net_4 ; 
 int /*<<< orphan*/  test_PACKET_get_sub_packet ; 
 int /*<<< orphan*/  test_PACKET_memdup ; 
 int /*<<< orphan*/  test_PACKET_null_init ; 
 int /*<<< orphan*/  test_PACKET_remaining ; 
 int /*<<< orphan*/  test_PACKET_strndup ; 

int setup_tests(void)
{
    unsigned int i;

    for (i = 1; i <= BUF_LEN; i++)
        smbuf[i - 1] = (i * 2) & 0xff;

    ADD_TEST(test_PACKET_buf_init);
    ADD_TEST(test_PACKET_null_init);
    ADD_TEST(test_PACKET_remaining);
    ADD_TEST(test_PACKET_end);
    ADD_TEST(test_PACKET_equal);
    ADD_TEST(test_PACKET_get_1);
    ADD_TEST(test_PACKET_get_4);
    ADD_TEST(test_PACKET_get_net_2);
    ADD_TEST(test_PACKET_get_net_3);
    ADD_TEST(test_PACKET_get_net_4);
    ADD_TEST(test_PACKET_get_sub_packet);
    ADD_TEST(test_PACKET_get_bytes);
    ADD_TEST(test_PACKET_copy_bytes);
    ADD_TEST(test_PACKET_copy_all);
    ADD_TEST(test_PACKET_memdup);
    ADD_TEST(test_PACKET_strndup);
    ADD_TEST(test_PACKET_contains_zero_byte);
    ADD_TEST(test_PACKET_forward);
    ADD_TEST(test_PACKET_get_length_prefixed_1);
    ADD_TEST(test_PACKET_get_length_prefixed_2);
    ADD_TEST(test_PACKET_get_length_prefixed_3);
    ADD_TEST(test_PACKET_as_length_prefixed_1);
    ADD_TEST(test_PACKET_as_length_prefixed_2);
    return 1;
}