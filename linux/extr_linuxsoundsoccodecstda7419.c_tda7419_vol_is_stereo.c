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
struct tda7419_vol_control {scalar_t__ reg; scalar_t__ rreg; } ;

/* Variables and functions */

__attribute__((used)) static inline bool tda7419_vol_is_stereo(struct tda7419_vol_control *tvc)
{
	if (tvc->reg == tvc->rreg)
		return false;

	return true;
}