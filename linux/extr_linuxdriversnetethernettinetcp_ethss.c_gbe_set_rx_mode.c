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
struct gbe_priv {int num_slaves; int /*<<< orphan*/  dev; int /*<<< orphan*/  ale_ports; struct cpsw_ale* ale; } ;
struct gbe_intf {struct gbe_priv* gbe_dev; } ;
struct cpsw_ale {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_AGEOUT ; 
 int /*<<< orphan*/  ALE_P0_UNI_FLOOD ; 
 int /*<<< orphan*/  ALE_PORT_NOLEARN ; 
 int /*<<< orphan*/  ALE_PORT_NO_SA_UPDATE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GBE_PORT_MASK (int /*<<< orphan*/ ) ; 
 unsigned long HZ ; 
 scalar_t__ cpsw_ale_control_get (struct cpsw_ale*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_ale_control_set (struct cpsw_ale*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpsw_ale_flush_multicast (struct cpsw_ale*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int gbe_set_rx_mode(void *intf_priv, bool promisc)
{
	struct gbe_intf *gbe_intf = intf_priv;
	struct gbe_priv *gbe_dev = gbe_intf->gbe_dev;
	struct cpsw_ale *ale = gbe_dev->ale;
	unsigned long timeout;
	int i, ret = -ETIMEDOUT;

	/* Disable(1)/Enable(0) Learn for all ports (host is port 0 and
	 * slaves are port 1 and up
	 */
	for (i = 0; i <= gbe_dev->num_slaves; i++) {
		cpsw_ale_control_set(ale, i,
				     ALE_PORT_NOLEARN, !!promisc);
		cpsw_ale_control_set(ale, i,
				     ALE_PORT_NO_SA_UPDATE, !!promisc);
	}

	if (!promisc) {
		/* Don't Flood All Unicast Packets to Host port */
		cpsw_ale_control_set(ale, 0, ALE_P0_UNI_FLOOD, 0);
		dev_vdbg(gbe_dev->dev, "promiscuous mode disabled\n");
		return 0;
	}

	timeout = jiffies + HZ;

	/* Clear All Untouched entries */
	cpsw_ale_control_set(ale, 0, ALE_AGEOUT, 1);
	do {
		cpu_relax();
		if (cpsw_ale_control_get(ale, 0, ALE_AGEOUT)) {
			ret = 0;
			break;
		}

	} while (time_after(timeout, jiffies));

	/* Make sure it is not a false timeout */
	if (ret && !cpsw_ale_control_get(ale, 0, ALE_AGEOUT))
		return ret;

	cpsw_ale_control_set(ale, 0, ALE_AGEOUT, 1);

	/* Clear all mcast from ALE */
	cpsw_ale_flush_multicast(ale,
				 GBE_PORT_MASK(gbe_dev->ale_ports),
				 -1);

	/* Flood All Unicast Packets to Host port */
	cpsw_ale_control_set(ale, 0, ALE_P0_UNI_FLOOD, 1);
	dev_vdbg(gbe_dev->dev, "promiscuous mode enabled\n");
	return ret;
}