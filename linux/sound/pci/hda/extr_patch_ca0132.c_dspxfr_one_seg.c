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
typedef  unsigned int u32 ;
struct hda_codec {int dummy; } ;
struct dsp_image_seg {unsigned int* data; unsigned int chip_addr; unsigned int count; } ;
struct dma_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_STATE_RUN ; 
 int /*<<< orphan*/  DMA_STATE_STOP ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ UC_RANGE (unsigned int,int) ; 
 int /*<<< orphan*/  X_RANGE_ALL (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Y_RANGE_ALL (unsigned int,unsigned int) ; 
 int chipio_write_multiple (struct hda_codec*,unsigned int,unsigned int const*,unsigned int) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,...) ; 
 unsigned char* dma_get_buffer_addr (struct dma_engine*) ; 
 scalar_t__ dma_get_buffer_size (struct dma_engine*) ; 
 int /*<<< orphan*/  dma_get_converter_format (struct dma_engine*,unsigned short*) ; 
 int dma_reset (struct dma_engine*) ; 
 int dma_set_state (struct dma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_xfer (struct dma_engine*,unsigned int const*,unsigned int) ; 
 int dsp_dma_setup (struct hda_codec*,unsigned int,unsigned int,unsigned int) ; 
 int dsp_dma_setup_common (struct hda_codec*,unsigned int,unsigned int,unsigned int,int) ; 
 int dsp_dma_start (struct hda_codec*,unsigned int,int) ; 
 int dsp_dma_stop (struct hda_codec*,unsigned int,int) ; 
 int dsp_is_dma_active (struct hda_codec*,unsigned int) ; 
 int dspxfr_hci_write (struct hda_codec*,struct dsp_image_seg const*) ; 
 int get_hdafmt_chs (unsigned short) ; 
 int get_hdafmt_rate (unsigned short) ; 
 struct dsp_image_seg* get_next_seg_ptr (struct dsp_image_seg const*) ; 
 scalar_t__ is_hci_prog_list_seg (struct dsp_image_seg const*) ; 
 scalar_t__ is_last (struct dsp_image_seg const*) ; 
 unsigned long jiffies ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int dspxfr_one_seg(struct hda_codec *codec,
			const struct dsp_image_seg *fls,
			unsigned int reloc,
			struct dma_engine *dma_engine,
			unsigned int dma_chan,
			unsigned int port_map_mask,
			bool ovly)
{
	int status = 0;
	bool comm_dma_setup_done = false;
	const unsigned int *data;
	unsigned int chip_addx;
	unsigned int words_to_write;
	unsigned int buffer_size_words;
	unsigned char *buffer_addx;
	unsigned short hda_format;
	unsigned int sample_rate_div;
	unsigned int sample_rate_mul;
	unsigned int num_chans;
	unsigned int hda_frame_size_words;
	unsigned int remainder_words;
	const u32 *data_remainder;
	u32 chip_addx_remainder;
	unsigned int run_size_words;
	const struct dsp_image_seg *hci_write = NULL;
	unsigned long timeout;
	bool dma_active;

	if (fls == NULL)
		return -EINVAL;
	if (is_hci_prog_list_seg(fls)) {
		hci_write = fls;
		fls = get_next_seg_ptr(fls);
	}

	if (hci_write && (!fls || is_last(fls))) {
		codec_dbg(codec, "hci_write\n");
		return dspxfr_hci_write(codec, hci_write);
	}

	if (fls == NULL || dma_engine == NULL || port_map_mask == 0) {
		codec_dbg(codec, "Invalid Params\n");
		return -EINVAL;
	}

	data = fls->data;
	chip_addx = fls->chip_addr,
	words_to_write = fls->count;

	if (!words_to_write)
		return hci_write ? dspxfr_hci_write(codec, hci_write) : 0;
	if (reloc)
		chip_addx = (chip_addx & (0xFFFF0000 << 2)) + (reloc << 2);

	if (!UC_RANGE(chip_addx, words_to_write) &&
	    !X_RANGE_ALL(chip_addx, words_to_write) &&
	    !Y_RANGE_ALL(chip_addx, words_to_write)) {
		codec_dbg(codec, "Invalid chip_addx Params\n");
		return -EINVAL;
	}

	buffer_size_words = (unsigned int)dma_get_buffer_size(dma_engine) /
					sizeof(u32);

	buffer_addx = dma_get_buffer_addr(dma_engine);

	if (buffer_addx == NULL) {
		codec_dbg(codec, "dma_engine buffer NULL\n");
		return -EINVAL;
	}

	dma_get_converter_format(dma_engine, &hda_format);
	sample_rate_div = ((get_hdafmt_rate(hda_format) >> 0) & 3) + 1;
	sample_rate_mul = ((get_hdafmt_rate(hda_format) >> 3) & 3) + 1;
	num_chans = get_hdafmt_chs(hda_format) + 1;

	hda_frame_size_words = ((sample_rate_div == 0) ? 0 :
			(num_chans * sample_rate_mul / sample_rate_div));

	if (hda_frame_size_words == 0) {
		codec_dbg(codec, "frmsz zero\n");
		return -EINVAL;
	}

	buffer_size_words = min(buffer_size_words,
				(unsigned int)(UC_RANGE(chip_addx, 1) ?
				65536 : 32768));
	buffer_size_words -= buffer_size_words % hda_frame_size_words;
	codec_dbg(codec,
		   "chpadr=0x%08x frmsz=%u nchan=%u "
		   "rate_mul=%u div=%u bufsz=%u\n",
		   chip_addx, hda_frame_size_words, num_chans,
		   sample_rate_mul, sample_rate_div, buffer_size_words);

	if (buffer_size_words < hda_frame_size_words) {
		codec_dbg(codec, "dspxfr_one_seg:failed\n");
		return -EINVAL;
	}

	remainder_words = words_to_write % hda_frame_size_words;
	data_remainder = data;
	chip_addx_remainder = chip_addx;

	data += remainder_words;
	chip_addx += remainder_words*sizeof(u32);
	words_to_write -= remainder_words;

	while (words_to_write != 0) {
		run_size_words = min(buffer_size_words, words_to_write);
		codec_dbg(codec, "dspxfr (seg loop)cnt=%u rs=%u remainder=%u\n",
			    words_to_write, run_size_words, remainder_words);
		dma_xfer(dma_engine, data, run_size_words*sizeof(u32));
		if (!comm_dma_setup_done) {
			status = dsp_dma_stop(codec, dma_chan, ovly);
			if (status < 0)
				return status;
			status = dsp_dma_setup_common(codec, chip_addx,
						dma_chan, port_map_mask, ovly);
			if (status < 0)
				return status;
			comm_dma_setup_done = true;
		}

		status = dsp_dma_setup(codec, chip_addx,
						run_size_words, dma_chan);
		if (status < 0)
			return status;
		status = dsp_dma_start(codec, dma_chan, ovly);
		if (status < 0)
			return status;
		if (!dsp_is_dma_active(codec, dma_chan)) {
			codec_dbg(codec, "dspxfr:DMA did not start\n");
			return -EIO;
		}
		status = dma_set_state(dma_engine, DMA_STATE_RUN);
		if (status < 0)
			return status;
		if (remainder_words != 0) {
			status = chipio_write_multiple(codec,
						chip_addx_remainder,
						data_remainder,
						remainder_words);
			if (status < 0)
				return status;
			remainder_words = 0;
		}
		if (hci_write) {
			status = dspxfr_hci_write(codec, hci_write);
			if (status < 0)
				return status;
			hci_write = NULL;
		}

		timeout = jiffies + msecs_to_jiffies(2000);
		do {
			dma_active = dsp_is_dma_active(codec, dma_chan);
			if (!dma_active)
				break;
			msleep(20);
		} while (time_before(jiffies, timeout));
		if (dma_active)
			break;

		codec_dbg(codec, "+++++ DMA complete\n");
		dma_set_state(dma_engine, DMA_STATE_STOP);
		status = dma_reset(dma_engine);

		if (status < 0)
			return status;

		data += run_size_words;
		chip_addx += run_size_words*sizeof(u32);
		words_to_write -= run_size_words;
	}

	if (remainder_words != 0) {
		status = chipio_write_multiple(codec, chip_addx_remainder,
					data_remainder, remainder_words);
	}

	return status;
}