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
typedef  int s16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int abs (int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool madera_eq_filter_unstable(bool mode, __be16 _a, __be16 _b)
{
	s16 a = be16_to_cpu(_a);
	s16 b = be16_to_cpu(_b);

	if (!mode) {
		return abs(a) >= 4096;
	} else {
		if (abs(b) >= 4096)
			return true;

		return (abs((a << 16) / (4096 - b)) >= 4096 << 4);
	}
}