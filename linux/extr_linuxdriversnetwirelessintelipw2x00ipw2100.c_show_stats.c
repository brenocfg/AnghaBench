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
struct ipw2100_priv {int interrupts; int tx_interrupts; int rx_interrupts; int inta_other; int resets; int hangs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct ipw2100_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static ssize_t show_stats(struct device *d, struct device_attribute *attr,
			  char *buf)
{
	struct ipw2100_priv *priv = dev_get_drvdata(d);
	char *out = buf;

	out += sprintf(out, "interrupts: %d {tx: %d, rx: %d, other: %d}\n",
		       priv->interrupts, priv->tx_interrupts,
		       priv->rx_interrupts, priv->inta_other);
	out += sprintf(out, "firmware resets: %d\n", priv->resets);
	out += sprintf(out, "firmware hangs: %d\n", priv->hangs);
#ifdef CONFIG_IPW2100_DEBUG
	out += sprintf(out, "packet mismatch image: %s\n",
		       priv->snapshot[0] ? "YES" : "NO");
#endif

	return out - buf;
}