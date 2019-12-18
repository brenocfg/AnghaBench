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
struct wmfw_v3_id_hdr {int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  ver; int /*<<< orphan*/  id; } ;
struct wm_adsp {int fw_id_version; void* fw_vendor_id; void* fw_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  adsp_info (struct wm_adsp*,char*,void*,void*,int,int,int,int) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wmfw_v3_parse_id_header(struct wm_adsp *dsp,
				    struct wmfw_v3_id_hdr *fw, int nalgs)
{
	dsp->fw_id = be32_to_cpu(fw->id);
	dsp->fw_id_version = be32_to_cpu(fw->ver);
	dsp->fw_vendor_id = be32_to_cpu(fw->vendor_id);

	adsp_info(dsp, "Firmware: %x vendor: 0x%x v%d.%d.%d, %d algorithms\n",
		  dsp->fw_id, dsp->fw_vendor_id,
		  (dsp->fw_id_version & 0xff0000) >> 16,
		  (dsp->fw_id_version & 0xff00) >> 8, dsp->fw_id_version & 0xff,
		  nalgs);
}