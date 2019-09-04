#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  data47; int /*<<< orphan*/  data03; } ;

/* Variables and functions */
 TYPE_1__* ehci_debug ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dbgp_get_data(void *buf, int size)
{
	unsigned char *bytes = buf;
	u32 lo, hi;
	int i;

	lo = readl(&ehci_debug->data03);
	hi = readl(&ehci_debug->data47);
	for (i = 0; i < 4 && i < size; i++)
		bytes[i] = (lo >> (8*i)) & 0xff;
	for (; i < 8 && i < size; i++)
		bytes[i] = (hi >> (8*(i - 4))) & 0xff;
}