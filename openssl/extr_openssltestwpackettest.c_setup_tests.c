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
 int /*<<< orphan*/  BUF_MEM_new () ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  test_WPACKET_allocate_bytes ; 
 int /*<<< orphan*/  test_WPACKET_init ; 
 int /*<<< orphan*/  test_WPACKET_memcpy ; 
 int /*<<< orphan*/  test_WPACKET_set_flags ; 
 int /*<<< orphan*/  test_WPACKET_set_max_size ; 
 int /*<<< orphan*/  test_WPACKET_start_sub_packet ; 

int setup_tests(void)
{
    if (!TEST_ptr(buf = BUF_MEM_new()))
            return 0;

    ADD_TEST(test_WPACKET_init);
    ADD_TEST(test_WPACKET_set_max_size);
    ADD_TEST(test_WPACKET_start_sub_packet);
    ADD_TEST(test_WPACKET_set_flags);
    ADD_TEST(test_WPACKET_allocate_bytes);
    ADD_TEST(test_WPACKET_memcpy);
    return 1;
}