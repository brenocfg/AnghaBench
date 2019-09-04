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

/* Variables and functions */
 scalar_t__ EISA_bus ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned short) ; 
 int /*<<< orphan*/  eisa_permute (unsigned short) ; 
 int /*<<< orphan*/  gsc_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void eisa_out16(unsigned short data, unsigned short port)
{
	if (EISA_bus)
		gsc_writew(cpu_to_le16(data), eisa_permute(port));
}