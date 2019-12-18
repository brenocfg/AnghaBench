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
struct noise_suppress_data {size_t channels; int /*<<< orphan*/  info_buffer; int /*<<< orphan*/ * output_buffers; int /*<<< orphan*/ * input_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_circlebuf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_data(struct noise_suppress_data *ng)
{
	for (size_t i = 0; i < ng->channels; i++) {
		clear_circlebuf(&ng->input_buffers[i]);
		clear_circlebuf(&ng->output_buffers[i]);
	}

	clear_circlebuf(&ng->info_buffer);
}