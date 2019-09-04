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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  c2p_unsupported () ; 

__attribute__((used)) static inline u32 get_mask(unsigned int n)
{
	switch (n) {
	case 1:
		return 0x55555555;

	case 2:
		return 0x33333333;

	case 4:
		return 0x0f0f0f0f;

	case 8:
		return 0x00ff00ff;

	case 16:
		return 0x0000ffff;
	}

	c2p_unsupported();
	return 0;
}