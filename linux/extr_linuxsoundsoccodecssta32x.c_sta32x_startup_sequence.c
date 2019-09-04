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
struct sta32x_priv {scalar_t__ gpiod_nreset; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int sta32x_startup_sequence(struct sta32x_priv *sta32x)
{
	if (sta32x->gpiod_nreset) {
		gpiod_set_value(sta32x->gpiod_nreset, 0);
		mdelay(1);
		gpiod_set_value(sta32x->gpiod_nreset, 1);
		mdelay(1);
	}

	return 0;
}