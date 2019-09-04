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
 int /*<<< orphan*/  eisa_permute (unsigned short) ; 
 int /*<<< orphan*/  gsc_writeb (unsigned char,int /*<<< orphan*/ ) ; 

void eisa_out8(unsigned char data, unsigned short port)
{
	if (EISA_bus)
		gsc_writeb(data, eisa_permute(port));
}