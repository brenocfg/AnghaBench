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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct wmfw_adsp2_id_hdr {int /*<<< orphan*/  zm; TYPE_2__ fw; int /*<<< orphan*/  ym; int /*<<< orphan*/  xm; int /*<<< orphan*/  n_algs; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  ver; } ;
struct wmfw_adsp2_alg_hdr {TYPE_1__ alg; int /*<<< orphan*/  zm; int /*<<< orphan*/  ym; int /*<<< orphan*/  xm; } ;
struct wm_adsp_region {int /*<<< orphan*/  base; } ;
struct wm_adsp_alg_region {TYPE_1__ alg; int /*<<< orphan*/  zm; int /*<<< orphan*/  ym; int /*<<< orphan*/  xm; } ;
struct wm_adsp {scalar_t__ fw_ver; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  adsp2_id ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct wmfw_adsp2_alg_hdr*) ; 
 int PTR_ERR (struct wmfw_adsp2_alg_hdr*) ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BYTES ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WMFW_ADSP2_XM ; 
 int /*<<< orphan*/  WMFW_ADSP2_YM ; 
 int /*<<< orphan*/  WMFW_ADSP2_ZM ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int) ; 
 int /*<<< orphan*/  adsp_info (struct wm_adsp*,char*,int,unsigned int,int,int,int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  adsp_warn (struct wm_adsp*,char*,unsigned int) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wmfw_adsp2_alg_hdr*) ; 
 int regmap_raw_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmfw_adsp2_id_hdr*,int) ; 
 int /*<<< orphan*/  wm_adsp_create_control (struct wm_adsp*,struct wmfw_adsp2_alg_hdr*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wmfw_adsp2_alg_hdr* wm_adsp_create_region (struct wm_adsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wm_adsp_region* wm_adsp_find_region (struct wm_adsp*,int /*<<< orphan*/ ) ; 
 struct wmfw_adsp2_alg_hdr* wm_adsp_read_algs (struct wm_adsp*,size_t,struct wm_adsp_region const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wmfw_parse_id_header (struct wm_adsp*,TYPE_2__*,size_t) ; 

__attribute__((used)) static int wm_adsp2_setup_algs(struct wm_adsp *dsp)
{
	struct wmfw_adsp2_id_hdr adsp2_id;
	struct wmfw_adsp2_alg_hdr *adsp2_alg;
	struct wm_adsp_alg_region *alg_region;
	const struct wm_adsp_region *mem;
	unsigned int pos, len;
	size_t n_algs;
	int i, ret;

	mem = wm_adsp_find_region(dsp, WMFW_ADSP2_XM);
	if (WARN_ON(!mem))
		return -EINVAL;

	ret = regmap_raw_read(dsp->regmap, mem->base, &adsp2_id,
			      sizeof(adsp2_id));
	if (ret != 0) {
		adsp_err(dsp, "Failed to read algorithm info: %d\n",
			 ret);
		return ret;
	}

	n_algs = be32_to_cpu(adsp2_id.n_algs);

	wmfw_parse_id_header(dsp, &adsp2_id.fw, n_algs);

	alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_XM,
					   adsp2_id.fw.id, adsp2_id.xm);
	if (IS_ERR(alg_region))
		return PTR_ERR(alg_region);

	alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_YM,
					   adsp2_id.fw.id, adsp2_id.ym);
	if (IS_ERR(alg_region))
		return PTR_ERR(alg_region);

	alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_ZM,
					   adsp2_id.fw.id, adsp2_id.zm);
	if (IS_ERR(alg_region))
		return PTR_ERR(alg_region);

	/* Calculate offset and length in DSP words */
	pos = sizeof(adsp2_id) / sizeof(u32);
	len = (sizeof(*adsp2_alg) * n_algs) / sizeof(u32);

	adsp2_alg = wm_adsp_read_algs(dsp, n_algs, mem, pos, len);
	if (IS_ERR(adsp2_alg))
		return PTR_ERR(adsp2_alg);

	for (i = 0; i < n_algs; i++) {
		adsp_info(dsp,
			  "%d: ID %x v%d.%d.%d XM@%x YM@%x ZM@%x\n",
			  i, be32_to_cpu(adsp2_alg[i].alg.id),
			  (be32_to_cpu(adsp2_alg[i].alg.ver) & 0xff0000) >> 16,
			  (be32_to_cpu(adsp2_alg[i].alg.ver) & 0xff00) >> 8,
			  be32_to_cpu(adsp2_alg[i].alg.ver) & 0xff,
			  be32_to_cpu(adsp2_alg[i].xm),
			  be32_to_cpu(adsp2_alg[i].ym),
			  be32_to_cpu(adsp2_alg[i].zm));

		alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_XM,
						   adsp2_alg[i].alg.id,
						   adsp2_alg[i].xm);
		if (IS_ERR(alg_region)) {
			ret = PTR_ERR(alg_region);
			goto out;
		}
		if (dsp->fw_ver == 0) {
			if (i + 1 < n_algs) {
				len = be32_to_cpu(adsp2_alg[i + 1].xm);
				len -= be32_to_cpu(adsp2_alg[i].xm);
				len *= 4;
				wm_adsp_create_control(dsp, alg_region, 0,
						     len, NULL, 0, 0,
						     SNDRV_CTL_ELEM_TYPE_BYTES);
			} else {
				adsp_warn(dsp, "Missing length info for region XM with ID %x\n",
					  be32_to_cpu(adsp2_alg[i].alg.id));
			}
		}

		alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_YM,
						   adsp2_alg[i].alg.id,
						   adsp2_alg[i].ym);
		if (IS_ERR(alg_region)) {
			ret = PTR_ERR(alg_region);
			goto out;
		}
		if (dsp->fw_ver == 0) {
			if (i + 1 < n_algs) {
				len = be32_to_cpu(adsp2_alg[i + 1].ym);
				len -= be32_to_cpu(adsp2_alg[i].ym);
				len *= 4;
				wm_adsp_create_control(dsp, alg_region, 0,
						     len, NULL, 0, 0,
						     SNDRV_CTL_ELEM_TYPE_BYTES);
			} else {
				adsp_warn(dsp, "Missing length info for region YM with ID %x\n",
					  be32_to_cpu(adsp2_alg[i].alg.id));
			}
		}

		alg_region = wm_adsp_create_region(dsp, WMFW_ADSP2_ZM,
						   adsp2_alg[i].alg.id,
						   adsp2_alg[i].zm);
		if (IS_ERR(alg_region)) {
			ret = PTR_ERR(alg_region);
			goto out;
		}
		if (dsp->fw_ver == 0) {
			if (i + 1 < n_algs) {
				len = be32_to_cpu(adsp2_alg[i + 1].zm);
				len -= be32_to_cpu(adsp2_alg[i].zm);
				len *= 4;
				wm_adsp_create_control(dsp, alg_region, 0,
						     len, NULL, 0, 0,
						     SNDRV_CTL_ELEM_TYPE_BYTES);
			} else {
				adsp_warn(dsp, "Missing length info for region ZM with ID %x\n",
					  be32_to_cpu(adsp2_alg[i].alg.id));
			}
		}
	}

out:
	kfree(adsp2_alg);
	return ret;
}