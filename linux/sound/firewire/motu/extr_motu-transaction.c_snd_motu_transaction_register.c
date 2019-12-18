#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; int /*<<< orphan*/ * address_callback; struct snd_motu* callback_data; } ;
struct snd_motu {TYPE_1__ async_handler; } ;
struct fw_address_region {int start; int end; } ;

/* Variables and functions */
 int fw_core_add_address_handler (TYPE_1__*,struct fw_address_region const*) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (TYPE_1__*) ; 
 int /*<<< orphan*/ * handle_message ; 
 int snd_motu_transaction_reregister (struct snd_motu*) ; 

int snd_motu_transaction_register(struct snd_motu *motu)
{
	static const struct fw_address_region resp_register_region = {
		.start	= 0xffffe0000000ull,
		.end	= 0xffffe000ffffull,
	};
	int err;

	/* Perhaps, 4 byte messages are transferred. */
	motu->async_handler.length = 4;
	motu->async_handler.address_callback = handle_message;
	motu->async_handler.callback_data = motu;

	err = fw_core_add_address_handler(&motu->async_handler,
					  &resp_register_region);
	if (err < 0)
		return err;

	err = snd_motu_transaction_reregister(motu);
	if (err < 0) {
		fw_core_remove_address_handler(&motu->async_handler);
		motu->async_handler.address_callback = NULL;
	}

	return err;
}