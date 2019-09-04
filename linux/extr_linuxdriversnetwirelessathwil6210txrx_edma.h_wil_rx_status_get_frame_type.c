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
struct TYPE_2__ {int /*<<< orphan*/  d1; } ;
struct wil_rx_status_extended {TYPE_1__ ext; } ;
struct wil6210_priv {scalar_t__ use_compressed_rx_status; } ;

/* Variables and functions */
 int IEEE80211_FTYPE_DATA ; 
 int WIL_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int wil_rx_status_get_frame_type(struct wil6210_priv *wil,
					       void *msg)
{
	if (wil->use_compressed_rx_status)
		return IEEE80211_FTYPE_DATA;

	return WIL_GET_BITS(((struct wil_rx_status_extended *)msg)->ext.d1,
			    0, 1) << 2;
}