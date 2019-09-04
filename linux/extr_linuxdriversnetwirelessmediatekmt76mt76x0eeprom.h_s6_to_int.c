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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int BIT (int) ; 
 int s6_validate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int s6_to_int(u32 reg)
{
	int s6;

	s6 = s6_validate(reg);
	if (s6 & BIT(5))
		s6 -= BIT(6);

	return s6;
}