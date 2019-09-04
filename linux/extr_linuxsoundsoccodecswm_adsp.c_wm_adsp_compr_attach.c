#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wm_adsp_compr {TYPE_2__* buf; TYPE_1__* dsp; } ;
struct TYPE_4__ {struct wm_adsp_compr* compr; } ;
struct TYPE_3__ {TYPE_2__* buffer; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int wm_adsp_compr_attach(struct wm_adsp_compr *compr)
{
	/*
	 * Note this will be more complex once each DSP can support multiple
	 * streams
	 */
	if (!compr->dsp->buffer)
		return -EINVAL;

	compr->buf = compr->dsp->buffer;
	compr->buf->compr = compr;

	return 0;
}