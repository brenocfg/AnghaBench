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
struct tfrc_rx_hist_entry {int dummy; } ;
struct tfrc_rx_hist {size_t loss_start; struct tfrc_rx_hist_entry** ring; } ;

/* Variables and functions */

__attribute__((used)) static inline struct tfrc_rx_hist_entry *
			tfrc_rx_hist_loss_prev(const struct tfrc_rx_hist *h)
{
	return h->ring[h->loss_start];
}