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
struct seq_file {int /*<<< orphan*/  private; } ;
struct qtnf_pcie_bus_priv {int /*<<< orphan*/  msi_enabled; } ;
struct qtnf_bus {int dummy; } ;

/* Variables and functions */
 struct qtnf_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct qtnf_pcie_bus_priv* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qtnf_dbg_msi_show(struct seq_file *s, void *data)
{
	struct qtnf_bus *bus = dev_get_drvdata(s->private);
	struct qtnf_pcie_bus_priv *priv = get_bus_priv(bus);

	seq_printf(s, "%u\n", priv->msi_enabled);

	return 0;
}