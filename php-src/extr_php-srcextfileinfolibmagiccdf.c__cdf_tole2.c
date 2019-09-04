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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t
_cdf_tole2(uint16_t sv)
{
	uint16_t rv;
	uint8_t *s = (uint8_t *)(void *)&sv;
	uint8_t *d = (uint8_t *)(void *)&rv;
	d[0] = s[1];
	d[1] = s[0];
	return rv;
}