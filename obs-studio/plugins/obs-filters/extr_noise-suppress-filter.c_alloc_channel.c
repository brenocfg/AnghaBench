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
typedef  int /*<<< orphan*/  uint32_t ;
struct noise_suppress_data {int /*<<< orphan*/ * output_buffers; int /*<<< orphan*/ * input_buffers; int /*<<< orphan*/ * states; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_reserve (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  speex_preprocess_state_init (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void alloc_channel(struct noise_suppress_data *ng,
				 uint32_t sample_rate, size_t channel,
				 size_t frames)
{
	ng->states[channel] =
		speex_preprocess_state_init((int)frames, sample_rate);

	circlebuf_reserve(&ng->input_buffers[channel], frames * sizeof(float));
	circlebuf_reserve(&ng->output_buffers[channel], frames * sizeof(float));
}