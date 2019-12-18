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
struct mime_header_encoder_data {int /*<<< orphan*/  tmpdev; int /*<<< orphan*/  outdev; int /*<<< orphan*/  encod_filter_backup; int /*<<< orphan*/  encod_filter; int /*<<< orphan*/  conv2_filter_backup; int /*<<< orphan*/  conv2_filter; int /*<<< orphan*/  block_filter; int /*<<< orphan*/  conv1_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_convert_filter_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbfl_free (void*) ; 
 int /*<<< orphan*/  mbfl_memory_device_clear (int /*<<< orphan*/ *) ; 

void
mime_header_encoder_delete(struct mime_header_encoder_data *pe)
{
	if (pe) {
		mbfl_convert_filter_delete(pe->conv1_filter);
		mbfl_convert_filter_delete(pe->block_filter);
		mbfl_convert_filter_delete(pe->conv2_filter);
		mbfl_convert_filter_delete(pe->conv2_filter_backup);
		mbfl_convert_filter_delete(pe->encod_filter);
		mbfl_convert_filter_delete(pe->encod_filter_backup);
		mbfl_memory_device_clear(&pe->outdev);
		mbfl_memory_device_clear(&pe->tmpdev);
		mbfl_free((void*)pe);
	}
}