#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  seq_num; } ;
struct wil_rx_status_extended {TYPE_1__ ext; } ;
struct wil6210_priv {scalar_t__ use_compressed_rx_status; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */

__attribute__((used)) static inline __le16 wil_rx_status_get_seq(struct wil6210_priv *wil, void *msg)
{
	if (wil->use_compressed_rx_status)
		return 0;

	return ((struct wil_rx_status_extended *)msg)->ext.seq_num;
}