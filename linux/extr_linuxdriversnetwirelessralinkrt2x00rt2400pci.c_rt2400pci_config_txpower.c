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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXPOWER_TO_DEV (int) ; 
 int /*<<< orphan*/  rt2400pci_bbp_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2400pci_config_txpower(struct rt2x00_dev *rt2x00dev, int txpower)
{
	rt2400pci_bbp_write(rt2x00dev, 3, TXPOWER_TO_DEV(txpower));
}