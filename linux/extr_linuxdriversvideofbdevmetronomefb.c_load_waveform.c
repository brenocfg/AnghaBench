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
typedef  int u8 ;
struct waveform_hdr {int fvsn; int wfm_cs; int mc; int trc; scalar_t__* stuff2a; int* wmta; unsigned char swtb; unsigned char endb; int /*<<< orphan*/  luts; } ;
struct metronomefb_par {int* metromem_wfm; size_t dt; int frame_count; TYPE_1__* info; } ;
struct device {int dummy; } ;
struct TYPE_4__ {size_t wfm_size; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int calc_cksum (int,int,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 TYPE_2__* epd_frame_table ; 
 int get_unaligned_le32 (int*) ; 
 size_t user_wfm_size ; 

__attribute__((used)) static int load_waveform(u8 *mem, size_t size, int m, int t,
			 struct metronomefb_par *par)
{
	int tta;
	int wmta;
	int trn = 0;
	int i;
	unsigned char v;
	u8 cksum;
	int cksum_idx;
	int wfm_idx, owfm_idx;
	int mem_idx = 0;
	struct waveform_hdr *wfm_hdr;
	u8 *metromem = par->metromem_wfm;
	struct device *dev = par->info->dev;

	if (user_wfm_size)
		epd_frame_table[par->dt].wfm_size = user_wfm_size;

	if (size != epd_frame_table[par->dt].wfm_size) {
		dev_err(dev, "Error: unexpected size %zd != %d\n", size,
					epd_frame_table[par->dt].wfm_size);
		return -EINVAL;
	}

	wfm_hdr = (struct waveform_hdr *) mem;

	if (wfm_hdr->fvsn != 1) {
		dev_err(dev, "Error: bad fvsn %x\n", wfm_hdr->fvsn);
		return -EINVAL;
	}
	if (wfm_hdr->luts != 0) {
		dev_err(dev, "Error: bad luts %x\n", wfm_hdr->luts);
		return -EINVAL;
	}
	cksum = calc_cksum(32, 47, mem);
	if (cksum != wfm_hdr->wfm_cs) {
		dev_err(dev, "Error: bad cksum %x != %x\n", cksum,
					wfm_hdr->wfm_cs);
		return -EINVAL;
	}
	wfm_hdr->mc += 1;
	wfm_hdr->trc += 1;
	for (i = 0; i < 5; i++) {
		if (*(wfm_hdr->stuff2a + i) != 0) {
			dev_err(dev, "Error: unexpected value in padding\n");
			return -EINVAL;
		}
	}

	/* calculating trn. trn is something used to index into
	the waveform. presumably selecting the right one for the
	desired temperature. it works out the offset of the first
	v that exceeds the specified temperature */
	if ((sizeof(*wfm_hdr) + wfm_hdr->trc) > size)
		return -EINVAL;

	for (i = sizeof(*wfm_hdr); i <= sizeof(*wfm_hdr) + wfm_hdr->trc; i++) {
		if (mem[i] > t) {
			trn = i - sizeof(*wfm_hdr) - 1;
			break;
		}
	}

	/* check temperature range table checksum */
	cksum_idx = sizeof(*wfm_hdr) + wfm_hdr->trc + 1;
	if (cksum_idx >= size)
		return -EINVAL;
	cksum = calc_cksum(sizeof(*wfm_hdr), cksum_idx, mem);
	if (cksum != mem[cksum_idx]) {
		dev_err(dev, "Error: bad temperature range table cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		return -EINVAL;
	}

	/* check waveform mode table address checksum */
	wmta = get_unaligned_le32(wfm_hdr->wmta) & 0x00FFFFFF;
	cksum_idx = wmta + m*4 + 3;
	if (cksum_idx >= size)
		return -EINVAL;
	cksum = calc_cksum(cksum_idx - 3, cksum_idx, mem);
	if (cksum != mem[cksum_idx]) {
		dev_err(dev, "Error: bad mode table address cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		return -EINVAL;
	}

	/* check waveform temperature table address checksum */
	tta = get_unaligned_le32(mem + wmta + m * 4) & 0x00FFFFFF;
	cksum_idx = tta + trn*4 + 3;
	if (cksum_idx >= size)
		return -EINVAL;
	cksum = calc_cksum(cksum_idx - 3, cksum_idx, mem);
	if (cksum != mem[cksum_idx]) {
		dev_err(dev, "Error: bad temperature table address cksum"
			" %x != %x\n", cksum, mem[cksum_idx]);
		return -EINVAL;
	}

	/* here we do the real work of putting the waveform into the
	metromem buffer. this does runlength decoding of the waveform */
	wfm_idx = get_unaligned_le32(mem + tta + trn * 4) & 0x00FFFFFF;
	owfm_idx = wfm_idx;
	if (wfm_idx >= size)
		return -EINVAL;
	while (wfm_idx < size) {
		unsigned char rl;
		v = mem[wfm_idx++];
		if (v == wfm_hdr->swtb) {
			while (((v = mem[wfm_idx++]) != wfm_hdr->swtb) &&
				wfm_idx < size)
				metromem[mem_idx++] = v;

			continue;
		}

		if (v == wfm_hdr->endb)
			break;

		rl = mem[wfm_idx++];
		for (i = 0; i <= rl; i++)
			metromem[mem_idx++] = v;
	}

	cksum_idx = wfm_idx;
	if (cksum_idx >= size)
		return -EINVAL;
	cksum = calc_cksum(owfm_idx, cksum_idx, mem);
	if (cksum != mem[cksum_idx]) {
		dev_err(dev, "Error: bad waveform data cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		return -EINVAL;
	}
	par->frame_count = (mem_idx/64);

	return 0;
}