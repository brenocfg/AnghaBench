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
typedef  size_t u8 ;
struct wil6210_priv {size_t max_vifs; int /*<<< orphan*/ * vifs; } ;

/* Variables and functions */
 size_t U8_MAX ; 

__attribute__((used)) static u8 wil_vif_find_free_mid(struct wil6210_priv *wil)
{
	u8 i;

	for (i = 0; i < wil->max_vifs; i++) {
		if (!wil->vifs[i])
			return i;
	}

	return U8_MAX;
}