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
struct TYPE_5__ {int max_block_id; TYPE_1__* blocks; scalar_t__ main_data_len; int /*<<< orphan*/ * decoded_record; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_4__ {int in_use; int has_image; int has_data; int apply_image; } ;

/* Variables and functions */

__attribute__((used)) static void
ResetDecoder(XLogReaderState *state)
{
	int			block_id;

	state->decoded_record = NULL;

	state->main_data_len = 0;

	for (block_id = 0; block_id <= state->max_block_id; block_id++)
	{
		state->blocks[block_id].in_use = false;
		state->blocks[block_id].has_image = false;
		state->blocks[block_id].has_data = false;
		state->blocks[block_id].apply_image = false;
	}
	state->max_block_id = -1;
}