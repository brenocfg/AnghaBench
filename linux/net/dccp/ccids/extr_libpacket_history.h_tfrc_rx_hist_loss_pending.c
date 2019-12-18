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
struct tfrc_rx_hist {scalar_t__ loss_count; } ;

/* Variables and functions */

__attribute__((used)) static inline bool tfrc_rx_hist_loss_pending(const struct tfrc_rx_hist *h)
{
	return h->loss_count > 0;
}