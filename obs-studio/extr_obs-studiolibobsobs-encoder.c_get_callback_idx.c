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
struct TYPE_2__ {size_t num; struct encoder_callback* array; } ;
struct obs_encoder {TYPE_1__ callbacks; } ;
struct encoder_callback {void (* new_packet ) (void*,struct encoder_packet*) ;void* param; } ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 

__attribute__((used)) static inline size_t get_callback_idx(
		const struct obs_encoder *encoder,
		void (*new_packet)(void *param, struct encoder_packet *packet),
		void *param)
{
	for (size_t i = 0; i < encoder->callbacks.num; i++) {
		struct encoder_callback *cb = encoder->callbacks.array+i;

		if (cb->new_packet == new_packet && cb->param == param)
			return i;
	}

	return DARRAY_INVALID;
}