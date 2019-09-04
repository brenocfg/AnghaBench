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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 phydm_adjust_pwdb(u8 cck_highpwr, u8 pwdb_all)
{
	if (!cck_highpwr) {
		if (pwdb_all >= 80)
			return ((pwdb_all - 80) << 1) + ((pwdb_all - 80) >> 1) +
			       80;
		else if ((pwdb_all <= 78) && (pwdb_all >= 20))
			return pwdb_all + 3;
		if (pwdb_all > 100)
			return 100;
	}
	return pwdb_all;
}