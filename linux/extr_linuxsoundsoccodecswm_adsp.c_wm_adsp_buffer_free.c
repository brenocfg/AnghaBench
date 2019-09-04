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
struct wm_adsp {TYPE_1__* buffer; } ;
struct TYPE_2__ {struct TYPE_2__* regions; int /*<<< orphan*/  compr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  wm_adsp_compr_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_adsp_buffer_free(struct wm_adsp *dsp)
{
	if (dsp->buffer) {
		wm_adsp_compr_detach(dsp->buffer->compr);

		kfree(dsp->buffer->regions);
		kfree(dsp->buffer);

		dsp->buffer = NULL;
	}

	return 0;
}