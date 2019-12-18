#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int offset; scalar_t__ length; struct snd_ff* callback_data; int /*<<< orphan*/  address_callback; } ;
struct snd_ff {TYPE_2__ async_handler; TYPE_1__* spec; } ;
struct fw_address_region {int start; scalar_t__ end; } ;
struct TYPE_4__ {scalar_t__ midi_addr_range; } ;

/* Variables and functions */
 int EAGAIN ; 
 int fw_core_add_address_handler (TYPE_2__*,struct fw_address_region*) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (TYPE_2__*) ; 
 int /*<<< orphan*/  handle_midi_msg ; 

__attribute__((used)) static int allocate_own_address(struct snd_ff *ff, int i)
{
	struct fw_address_region midi_msg_region;
	int err;

	ff->async_handler.length = ff->spec->midi_addr_range;
	ff->async_handler.address_callback = handle_midi_msg;
	ff->async_handler.callback_data = ff;

	midi_msg_region.start = 0x000100000000ull * i;
	midi_msg_region.end = midi_msg_region.start + ff->async_handler.length;

	err = fw_core_add_address_handler(&ff->async_handler, &midi_msg_region);
	if (err >= 0) {
		/* Controllers are allowed to register this region. */
		if (ff->async_handler.offset & 0x0000ffffffff) {
			fw_core_remove_address_handler(&ff->async_handler);
			err = -EAGAIN;
		}
	}

	return err;
}