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
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_pcie_disable_host_int (struct mwifiex_adapter*) ; 

__attribute__((used)) static void mwifiex_pcie_disable_host_int_noerr(struct mwifiex_adapter *adapter)
{
	WARN_ON(mwifiex_pcie_disable_host_int(adapter));
}