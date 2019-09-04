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
struct tegra_pcie {int /*<<< orphan*/  debugfs; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct tegra_pcie*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_pcie_debugfs_exit (struct tegra_pcie*) ; 
 int /*<<< orphan*/  tegra_pcie_ports_ops ; 

__attribute__((used)) static int tegra_pcie_debugfs_init(struct tegra_pcie *pcie)
{
	struct dentry *file;

	pcie->debugfs = debugfs_create_dir("pcie", NULL);
	if (!pcie->debugfs)
		return -ENOMEM;

	file = debugfs_create_file("ports", S_IFREG | S_IRUGO, pcie->debugfs,
				   pcie, &tegra_pcie_ports_ops);
	if (!file)
		goto remove;

	return 0;

remove:
	tegra_pcie_debugfs_exit(pcie);
	return -ENOMEM;
}