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
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static inline bool
spi_match(u_int32_t min, u_int32_t max, u_int32_t spi, bool invert)
{
	bool r;
	pr_debug("spi_match:%c 0x%x <= 0x%x <= 0x%x\n",
		 invert ? '!' : ' ', min, spi, max);
	r = (spi >= min && spi <= max) ^ invert;
	pr_debug(" result %s\n", r ? "PASS" : "FAILED");
	return r;
}