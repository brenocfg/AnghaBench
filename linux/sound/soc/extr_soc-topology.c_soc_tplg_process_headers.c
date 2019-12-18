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
struct soc_tplg {scalar_t__ pass; int /*<<< orphan*/  dev; scalar_t__ hdr_pos; TYPE_1__* fw; } ;
struct snd_soc_tplg_hdr {int /*<<< orphan*/  payload_size; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ SOC_TPLG_PASS_END ; 
 scalar_t__ SOC_TPLG_PASS_START ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int soc_tplg_dapm_complete (struct soc_tplg*) ; 
 int /*<<< orphan*/  soc_tplg_is_eof (struct soc_tplg*) ; 
 int soc_tplg_load_header (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 
 int soc_valid_header (struct soc_tplg*,struct snd_soc_tplg_hdr*) ; 

__attribute__((used)) static int soc_tplg_process_headers(struct soc_tplg *tplg)
{
	struct snd_soc_tplg_hdr *hdr;
	int ret;

	tplg->pass = SOC_TPLG_PASS_START;

	/* process the header types from start to end */
	while (tplg->pass <= SOC_TPLG_PASS_END) {

		tplg->hdr_pos = tplg->fw->data;
		hdr = (struct snd_soc_tplg_hdr *)tplg->hdr_pos;

		while (!soc_tplg_is_eof(tplg)) {

			/* make sure header is valid before loading */
			ret = soc_valid_header(tplg, hdr);
			if (ret < 0)
				return ret;
			else if (ret == 0)
				break;

			/* load the header object */
			ret = soc_tplg_load_header(tplg, hdr);
			if (ret < 0)
				return ret;

			/* goto next header */
			tplg->hdr_pos += le32_to_cpu(hdr->payload_size) +
				sizeof(struct snd_soc_tplg_hdr);
			hdr = (struct snd_soc_tplg_hdr *)tplg->hdr_pos;
		}

		/* next data type pass */
		tplg->pass++;
	}

	/* signal DAPM we are complete */
	ret = soc_tplg_dapm_complete(tplg);
	if (ret < 0)
		dev_err(tplg->dev,
			"ASoC: failed to initialise DAPM from Firmware\n");

	return ret;
}