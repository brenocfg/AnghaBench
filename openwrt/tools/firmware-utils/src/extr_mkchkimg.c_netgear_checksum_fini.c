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
typedef  int uint32_t ;
struct ngr_checksum {int c0; int c1; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long
netgear_checksum_fini (struct ngr_checksum * c)
{
	uint32_t b, checksum;

	b = (c->c0 & 65535) + ((c->c0 >> 16) & 65535);
	c->c0 = ((b >> 16) + b) & 65535;
	b = (c->c1 & 65535) + ((c->c1 >> 16) & 65535);
	c->c1 = ((b >> 16) + b) & 65535;
	checksum = ((c->c1 << 16) | c->c0);
	return checksum;
}