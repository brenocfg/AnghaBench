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
struct wm_adsp_compr {TYPE_1__* buf; scalar_t__ stream; } ;
struct TYPE_2__ {int /*<<< orphan*/ * compr; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_compr_fragment_elapsed (scalar_t__) ; 
 scalar_t__ wm_adsp_compr_attached (struct wm_adsp_compr*) ; 

__attribute__((used)) static void wm_adsp_compr_detach(struct wm_adsp_compr *compr)
{
	if (!compr)
		return;

	/* Wake the poll so it can see buffer is no longer attached */
	if (compr->stream)
		snd_compr_fragment_elapsed(compr->stream);

	if (wm_adsp_compr_attached(compr)) {
		compr->buf->compr = NULL;
		compr->buf = NULL;
	}
}