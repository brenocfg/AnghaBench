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
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_null_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_PACKET_null_init(void)
{
    PACKET pkt;

    PACKET_null_init(&pkt);
    if (!TEST_size_t_eq(PACKET_remaining(&pkt), 0)
            || !TEST_false(PACKET_forward(&pkt, 1)))
        return 0;

    return 1;
}