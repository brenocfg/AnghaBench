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
struct spi_master {int dummy; } ;
struct sh_msiof_spi_priv {int slave_aborted; int /*<<< orphan*/  done_txdma; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct sh_msiof_spi_priv* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int sh_msiof_slave_abort(struct spi_master *master)
{
	struct sh_msiof_spi_priv *p = spi_master_get_devdata(master);

	p->slave_aborted = true;
	complete(&p->done);
	complete(&p->done_txdma);
	return 0;
}