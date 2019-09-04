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
struct tegra_pcie {int dummy; } ;
struct seq_file {struct tegra_pcie* private; } ;
struct inode {struct tegra_pcie* i_private; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_pcie_ports_seq_ops ; 

__attribute__((used)) static int tegra_pcie_ports_open(struct inode *inode, struct file *file)
{
	struct tegra_pcie *pcie = inode->i_private;
	struct seq_file *s;
	int err;

	err = seq_open(file, &tegra_pcie_ports_seq_ops);
	if (err)
		return err;

	s = file->private_data;
	s->private = pcie;

	return 0;
}