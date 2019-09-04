#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_replaced_transfers {size_t inserted; TYPE_1__* inserted_transfers; int /*<<< orphan*/  replaced_after; int /*<<< orphan*/  replaced_transfers; int /*<<< orphan*/  (* release ) (struct spi_controller*,struct spi_message*,void*) ;} ;
struct spi_message {int dummy; } ;
struct spi_controller {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spi_controller*,struct spi_message*,void*) ; 

__attribute__((used)) static void __spi_replace_transfers_release(struct spi_controller *ctlr,
					    struct spi_message *msg,
					    void *res)
{
	struct spi_replaced_transfers *rxfer = res;
	size_t i;

	/* call extra callback if requested */
	if (rxfer->release)
		rxfer->release(ctlr, msg, res);

	/* insert replaced transfers back into the message */
	list_splice(&rxfer->replaced_transfers, rxfer->replaced_after);

	/* remove the formerly inserted entries */
	for (i = 0; i < rxfer->inserted; i++)
		list_del(&rxfer->inserted_transfers[i].transfer_list);
}