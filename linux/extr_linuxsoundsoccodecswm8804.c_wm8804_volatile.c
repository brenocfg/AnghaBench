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
struct device {int dummy; } ;

/* Variables and functions */
#define  WM8804_DEVID2 137 
#define  WM8804_DEVREV 136 
#define  WM8804_INTSTAT 135 
#define  WM8804_RST_DEVID1 134 
#define  WM8804_RXCHAN1 133 
#define  WM8804_RXCHAN2 132 
#define  WM8804_RXCHAN3 131 
#define  WM8804_RXCHAN4 130 
#define  WM8804_RXCHAN5 129 
#define  WM8804_SPDSTAT 128 

__attribute__((used)) static bool wm8804_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8804_RST_DEVID1:
	case WM8804_DEVID2:
	case WM8804_DEVREV:
	case WM8804_INTSTAT:
	case WM8804_SPDSTAT:
	case WM8804_RXCHAN1:
	case WM8804_RXCHAN2:
	case WM8804_RXCHAN3:
	case WM8804_RXCHAN4:
	case WM8804_RXCHAN5:
		return true;
	default:
		return false;
	}
}