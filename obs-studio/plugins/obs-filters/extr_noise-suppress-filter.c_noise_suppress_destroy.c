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
struct noise_suppress_data {size_t channels; int /*<<< orphan*/  output_data; int /*<<< orphan*/  info_buffer; struct noise_suppress_data** copy_buffers; struct noise_suppress_data** segment_buffers; int /*<<< orphan*/ * output_buffers; int /*<<< orphan*/ * input_buffers; int /*<<< orphan*/ * states; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct noise_suppress_data*) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speex_preprocess_state_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void noise_suppress_destroy(void *data)
{
	struct noise_suppress_data *ng = data;

	for (size_t i = 0; i < ng->channels; i++) {
		speex_preprocess_state_destroy(ng->states[i]);
		circlebuf_free(&ng->input_buffers[i]);
		circlebuf_free(&ng->output_buffers[i]);
	}

	bfree(ng->segment_buffers[0]);
	bfree(ng->copy_buffers[0]);
	circlebuf_free(&ng->info_buffer);
	da_free(ng->output_data);
	bfree(ng);
}