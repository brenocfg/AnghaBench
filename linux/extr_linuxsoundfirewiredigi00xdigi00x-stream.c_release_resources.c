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
struct snd_dg00x {int /*<<< orphan*/  rx_resources; int /*<<< orphan*/  tx_resources; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ DG00X_ADDR_BASE ; 
 scalar_t__ DG00X_OFFSET_ISOC_CHANNELS ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  fw_iso_resources_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_resources(struct snd_dg00x *dg00x)
{
	__be32 data = 0;

	/* Unregister isochronous channels for both direction. */
	snd_fw_transaction(dg00x->unit, TCODE_WRITE_QUADLET_REQUEST,
			   DG00X_ADDR_BASE + DG00X_OFFSET_ISOC_CHANNELS,
			   &data, sizeof(data), 0);

	/* Release isochronous resources. */
	fw_iso_resources_free(&dg00x->tx_resources);
	fw_iso_resources_free(&dg00x->rx_resources);
}