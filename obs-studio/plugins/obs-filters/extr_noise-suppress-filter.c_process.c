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
struct noise_suppress_data {size_t channels; float** copy_buffers; int frames; int /*<<< orphan*/ * output_buffers; scalar_t__** segment_buffers; int /*<<< orphan*/ * states; int /*<<< orphan*/  suppress_level; int /*<<< orphan*/ * input_buffers; } ;
typedef  scalar_t__ spx_int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPEEX_PREPROCESS_SET_NOISE_SUPPRESS ; 
 float c_16_to_32 ; 
 float c_32_to_16 ; 
 int /*<<< orphan*/  circlebuf_pop_front (int /*<<< orphan*/ *,float*,int) ; 
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,float*,int) ; 
 int /*<<< orphan*/  speex_preprocess_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speex_preprocess_run (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline void process(struct noise_suppress_data *ng)
{
	/* Pop from input circlebuf */
	for (size_t i = 0; i < ng->channels; i++)
		circlebuf_pop_front(&ng->input_buffers[i], ng->copy_buffers[i],
				    ng->frames * sizeof(float));

	/* Set args */
	for (size_t i = 0; i < ng->channels; i++)
		speex_preprocess_ctl(ng->states[i],
				     SPEEX_PREPROCESS_SET_NOISE_SUPPRESS,
				     &ng->suppress_level);

	/* Convert to 16bit */
	for (size_t i = 0; i < ng->channels; i++)
		for (size_t j = 0; j < ng->frames; j++) {
			float s = ng->copy_buffers[i][j];
			if (s > 1.0f)
				s = 1.0f;
			else if (s < -1.0f)
				s = -1.0f;
			ng->segment_buffers[i][j] =
				(spx_int16_t)(s * c_32_to_16);
		}

	/* Execute */
	for (size_t i = 0; i < ng->channels; i++)
		speex_preprocess_run(ng->states[i], ng->segment_buffers[i]);

	/* Convert back to 32bit */
	for (size_t i = 0; i < ng->channels; i++)
		for (size_t j = 0; j < ng->frames; j++)
			ng->copy_buffers[i][j] =
				(float)ng->segment_buffers[i][j] / c_16_to_32;

	/* Push to output circlebuf */
	for (size_t i = 0; i < ng->channels; i++)
		circlebuf_push_back(&ng->output_buffers[i], ng->copy_buffers[i],
				    ng->frames * sizeof(float));
}