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
struct spi_transfer {int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  speed_hz; } ;
struct spi_device {int /*<<< orphan*/  mode; } ;
struct bcm_qspi_parms {int /*<<< orphan*/  mode; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  speed_hz; } ;
struct bcm_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_qspi_hw_set_parms (struct bcm_qspi*,struct bcm_qspi_parms*) ; 

__attribute__((used)) static void bcm_qspi_update_parms(struct bcm_qspi *qspi,
				  struct spi_device *spi,
				  struct spi_transfer *trans)
{
	struct bcm_qspi_parms xp;

	xp.speed_hz = trans->speed_hz;
	xp.bits_per_word = trans->bits_per_word;
	xp.mode = spi->mode;

	bcm_qspi_hw_set_parms(qspi, &xp);
}