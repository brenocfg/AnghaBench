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
typedef  int /*<<< orphan*/  u8 ;
struct htt_rx_test {int num_ints; int /*<<< orphan*/ * payload; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */

__attribute__((used)) static inline u8 *htt_rx_test_get_chars(struct htt_rx_test *rx_test)
{
	return rx_test->payload + (rx_test->num_ints * sizeof(__le32));
}