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
struct mime_header_decoder_data {int /*<<< orphan*/  tmpdev; int /*<<< orphan*/  outdev; int /*<<< orphan*/  deco_filter; int /*<<< orphan*/  conv1_filter; int /*<<< orphan*/  conv2_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_convert_filter_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbfl_free (void*) ; 
 int /*<<< orphan*/  mbfl_memory_device_clear (int /*<<< orphan*/ *) ; 

void
mime_header_decoder_delete(struct mime_header_decoder_data *pd)
{
	if (pd) {
		mbfl_convert_filter_delete(pd->conv2_filter);
		mbfl_convert_filter_delete(pd->conv1_filter);
		mbfl_convert_filter_delete(pd->deco_filter);
		mbfl_memory_device_clear(&pd->outdev);
		mbfl_memory_device_clear(&pd->tmpdev);
		mbfl_free((void*)pd);
	}
}