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
struct fw_card {int gap_count; } ;

/* Variables and functions */

__attribute__((used)) static int current_bandwidth_overhead(struct fw_card *card)
{
	/*
	 * Under the usual pessimistic assumption (cable length 4.5 m), the
	 * isochronous overhead for N cables is 1.797 µs + N * 0.494 µs, or
	 * 88.3 + N * 24.3 in bandwidth units.
	 *
	 * The calculation below tries to deduce N from the current gap count.
	 * If the gap count has been optimized by measuring the actual packet
	 * transmission time, this derived overhead should be near the actual
	 * overhead as well.
	 */
	return card->gap_count < 63 ? card->gap_count * 97 / 10 + 89 : 512;
}