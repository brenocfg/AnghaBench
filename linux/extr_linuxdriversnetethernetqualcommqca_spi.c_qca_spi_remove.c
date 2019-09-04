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
struct spi_device {int dummy; } ;
struct qcaspi {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qcaspi_remove_device_debugfs (struct qcaspi*) ; 
 struct net_device* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int
qca_spi_remove(struct spi_device *spi)
{
	struct net_device *qcaspi_devs = spi_get_drvdata(spi);
	struct qcaspi *qca = netdev_priv(qcaspi_devs);

	qcaspi_remove_device_debugfs(qca);

	unregister_netdev(qcaspi_devs);
	free_netdev(qcaspi_devs);

	return 0;
}