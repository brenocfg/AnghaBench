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
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  PACKET_contains_zero_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 

__attribute__((used)) static int test_PACKET_contains_zero_byte(void)
{
    char buf1[10], buf2[10];
    PACKET pkt;

    memset(buf1, 'x', 10);
    memset(buf2, 'y', 10);
    buf2[5] = '\0';

    if (!TEST_true(PACKET_buf_init(&pkt, (unsigned char*)buf1, 10))
            || !TEST_false(PACKET_contains_zero_byte(&pkt))
            || !TEST_true(PACKET_buf_init(&pkt, (unsigned char*)buf2, 10))
            || !TEST_true(PACKET_contains_zero_byte(&pkt)))
        return 0;

    return 1;
}