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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmfw_adsp_alg_data {int /*<<< orphan*/  ncoeff; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/ * data; } ;
struct wm_coeff_parsed_alg {void* ncoeff; int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; void* id; } ;
struct wm_adsp {int fw_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,void*,...) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 void* wm_coeff_parse_int (int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  wm_coeff_parse_string (int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void wm_coeff_parse_alg(struct wm_adsp *dsp, const u8 **data,
				      struct wm_coeff_parsed_alg *blk)
{
	const struct wmfw_adsp_alg_data *raw;

	switch (dsp->fw_ver) {
	case 0:
	case 1:
		raw = (const struct wmfw_adsp_alg_data *)*data;
		*data = raw->data;

		blk->id = le32_to_cpu(raw->id);
		blk->name = raw->name;
		blk->name_len = strlen(raw->name);
		blk->ncoeff = le32_to_cpu(raw->ncoeff);
		break;
	default:
		blk->id = wm_coeff_parse_int(sizeof(raw->id), data);
		blk->name_len = wm_coeff_parse_string(sizeof(u8), data,
						      &blk->name);
		wm_coeff_parse_string(sizeof(u16), data, NULL);
		blk->ncoeff = wm_coeff_parse_int(sizeof(raw->ncoeff), data);
		break;
	}

	adsp_dbg(dsp, "Algorithm ID: %#x\n", blk->id);
	adsp_dbg(dsp, "Algorithm name: %.*s\n", blk->name_len, blk->name);
	adsp_dbg(dsp, "# of coefficient descriptors: %#x\n", blk->ncoeff);
}