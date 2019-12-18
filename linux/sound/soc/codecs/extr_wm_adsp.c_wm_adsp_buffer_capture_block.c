#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wm_adsp_compr_buf {scalar_t__ read_index; int avail; TYPE_3__* dsp; TYPE_2__* regions; } ;
struct wm_adsp_compr {int /*<<< orphan*/  raw_buf; struct wm_adsp_compr_buf* buf; } ;
struct TYPE_8__ {TYPE_1__* caps; } ;
struct TYPE_7__ {size_t fw; } ;
struct TYPE_6__ {scalar_t__ cumulative_size; int mem_type; unsigned int base_addr; unsigned int offset; } ;
struct TYPE_5__ {int num_regions; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HOST_BUFFER_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_ADSP_DATA_WORD_SIZE ; 
 int /*<<< orphan*/  next_read_index ; 
 scalar_t__ wm_adsp_buffer_size (struct wm_adsp_compr_buf*) ; 
 int wm_adsp_buffer_write (struct wm_adsp_compr_buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int wm_adsp_compr_frag_words (struct wm_adsp_compr*) ; 
 TYPE_4__* wm_adsp_fw ; 
 int wm_adsp_read_data_block (TYPE_3__*,int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_adsp_remove_padding (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_adsp_buffer_capture_block(struct wm_adsp_compr *compr, int target)
{
	struct wm_adsp_compr_buf *buf = compr->buf;
	unsigned int adsp_addr;
	int mem_type, nwords, max_read;
	int i, ret;

	/* Calculate read parameters */
	for (i = 0; i < wm_adsp_fw[buf->dsp->fw].caps->num_regions; ++i)
		if (buf->read_index < buf->regions[i].cumulative_size)
			break;

	if (i == wm_adsp_fw[buf->dsp->fw].caps->num_regions)
		return -EINVAL;

	mem_type = buf->regions[i].mem_type;
	adsp_addr = buf->regions[i].base_addr +
		    (buf->read_index - buf->regions[i].offset);

	max_read = wm_adsp_compr_frag_words(compr);
	nwords = buf->regions[i].cumulative_size - buf->read_index;

	if (nwords > target)
		nwords = target;
	if (nwords > buf->avail)
		nwords = buf->avail;
	if (nwords > max_read)
		nwords = max_read;
	if (!nwords)
		return 0;

	/* Read data from DSP */
	ret = wm_adsp_read_data_block(buf->dsp, mem_type, adsp_addr,
				      nwords, compr->raw_buf);
	if (ret < 0)
		return ret;

	wm_adsp_remove_padding(compr->raw_buf, nwords, WM_ADSP_DATA_WORD_SIZE);

	/* update read index to account for words read */
	buf->read_index += nwords;
	if (buf->read_index == wm_adsp_buffer_size(buf))
		buf->read_index = 0;

	ret = wm_adsp_buffer_write(buf, HOST_BUFFER_FIELD(next_read_index),
				   buf->read_index);
	if (ret < 0)
		return ret;

	/* update avail to account for words read */
	buf->avail -= nwords;

	return nwords;
}