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
struct ad193x_priv {int type; } ;

/* Variables and functions */
#define  AD1933 129 
#define  AD1934 128 

__attribute__((used)) static inline bool ad193x_has_adc(const struct ad193x_priv *ad193x)
{
	switch (ad193x->type) {
	case AD1933:
	case AD1934:
		return false;
	default:
		break;
	}

	return true;
}