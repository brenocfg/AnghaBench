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
struct wm_adsp_compr_buf {struct wm_adsp_compr_buf* regions; struct wm_adsp* dsp; } ;
struct wm_adsp {size_t fw; struct wm_adsp_compr_buf* buffer; } ;
struct TYPE_4__ {TYPE_1__* caps; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_regions; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int) ; 
 struct wm_adsp_compr_buf* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wm_adsp_compr_buf*) ; 
 struct wm_adsp_compr_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_adsp_buffer_clear (struct wm_adsp_compr_buf*) ; 
 int wm_adsp_buffer_locate (struct wm_adsp_compr_buf*) ; 
 int wm_adsp_buffer_populate (struct wm_adsp_compr_buf*) ; 
 TYPE_2__* wm_adsp_fw ; 

__attribute__((used)) static int wm_adsp_buffer_init(struct wm_adsp *dsp)
{
	struct wm_adsp_compr_buf *buf;
	int ret;

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf->dsp = dsp;

	wm_adsp_buffer_clear(buf);

	ret = wm_adsp_buffer_locate(buf);
	if (ret < 0) {
		adsp_err(dsp, "Failed to acquire host buffer: %d\n", ret);
		goto err_buffer;
	}

	buf->regions = kcalloc(wm_adsp_fw[dsp->fw].caps->num_regions,
			       sizeof(*buf->regions), GFP_KERNEL);
	if (!buf->regions) {
		ret = -ENOMEM;
		goto err_buffer;
	}

	ret = wm_adsp_buffer_populate(buf);
	if (ret < 0) {
		adsp_err(dsp, "Failed to populate host buffer: %d\n", ret);
		goto err_regions;
	}

	dsp->buffer = buf;

	return 0;

err_regions:
	kfree(buf->regions);
err_buffer:
	kfree(buf);
	return ret;
}