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
struct TYPE_2__ {int /*<<< orphan*/ * address_callback; } ;
struct snd_motu {TYPE_1__ async_handler; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_ADDR_HI ; 
 int /*<<< orphan*/  ASYNC_ADDR_LO ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_motu_transaction_write (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void snd_motu_transaction_unregister(struct snd_motu *motu)
{
	__be32 data;

	if (motu->async_handler.address_callback != NULL)
		fw_core_remove_address_handler(&motu->async_handler);
	motu->async_handler.address_callback = NULL;

	/* Unregister the address. */
	data = cpu_to_be32(0x00000000);
	snd_motu_transaction_write(motu, ASYNC_ADDR_HI, &data, sizeof(data));
	snd_motu_transaction_write(motu, ASYNC_ADDR_LO, &data, sizeof(data));
}