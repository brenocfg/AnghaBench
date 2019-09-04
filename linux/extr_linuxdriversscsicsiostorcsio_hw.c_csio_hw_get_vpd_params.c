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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct t4_vpd_hdr {int* id_data; } ;
struct csio_vpd {int /*<<< orphan*/  sn; int /*<<< orphan*/  ec; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  vpd_cap_addr; } ;
struct TYPE_4__ {TYPE_1__ pci; } ;
struct csio_hw {int /*<<< orphan*/  flags; TYPE_2__ params; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HWF_VPD_VALID ; 
 int /*<<< orphan*/  EC_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ID_LEN ; 
 int /*<<< orphan*/  PCI_CAP_ID_VPD ; 
 int /*<<< orphan*/  SERNUM_LEN ; 
 int VPD_BASE ; 
 int VPD_BASE_OLD ; 
 int VPD_INFO_FLD_HDR_SIZE ; 
 int VPD_LEN ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,...) ; 
 int csio_hw_get_vpd_keyword_val (struct t4_vpd_hdr const*,char*) ; 
 int csio_hw_seeprom_read (struct csio_hw*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ csio_is_valid_vpd (struct csio_hw*) ; 
 int csio_pci_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_valid_vpd_copied (struct csio_hw*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 char* strstrip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csio_hw_get_vpd_params(struct csio_hw *hw, struct csio_vpd *p)
{
	int i, ret, ec, sn, addr;
	uint8_t *vpd, csum;
	const struct t4_vpd_hdr *v;
	/* To get around compilation warning from strstrip */
	char *s;

	if (csio_is_valid_vpd(hw))
		return 0;

	ret = csio_pci_capability(hw->pdev, PCI_CAP_ID_VPD,
				  &hw->params.pci.vpd_cap_addr);
	if (ret)
		return -EINVAL;

	vpd = kzalloc(VPD_LEN, GFP_ATOMIC);
	if (vpd == NULL)
		return -ENOMEM;

	/*
	 * Card information normally starts at VPD_BASE but early cards had
	 * it at 0.
	 */
	ret = csio_hw_seeprom_read(hw, VPD_BASE, (uint32_t *)(vpd));
	addr = *vpd == 0x82 ? VPD_BASE : VPD_BASE_OLD;

	for (i = 0; i < VPD_LEN; i += 4) {
		ret = csio_hw_seeprom_read(hw, addr + i, (uint32_t *)(vpd + i));
		if (ret) {
			kfree(vpd);
			return ret;
		}
	}

	/* Reset the VPD flag! */
	hw->flags &= (~CSIO_HWF_VPD_VALID);

	v = (const struct t4_vpd_hdr *)vpd;

#define FIND_VPD_KW(var, name) do { \
	var = csio_hw_get_vpd_keyword_val(v, name); \
	if (var < 0) { \
		csio_err(hw, "missing VPD keyword " name "\n"); \
		kfree(vpd); \
		return -EINVAL; \
	} \
} while (0)

	FIND_VPD_KW(i, "RV");
	for (csum = 0; i >= 0; i--)
		csum += vpd[i];

	if (csum) {
		csio_err(hw, "corrupted VPD EEPROM, actual csum %u\n", csum);
		kfree(vpd);
		return -EINVAL;
	}
	FIND_VPD_KW(ec, "EC");
	FIND_VPD_KW(sn, "SN");
#undef FIND_VPD_KW

	memcpy(p->id, v->id_data, ID_LEN);
	s = strstrip(p->id);
	memcpy(p->ec, vpd + ec, EC_LEN);
	s = strstrip(p->ec);
	i = vpd[sn - VPD_INFO_FLD_HDR_SIZE + 2];
	memcpy(p->sn, vpd + sn, min(i, SERNUM_LEN));
	s = strstrip(p->sn);

	csio_valid_vpd_copied(hw);

	kfree(vpd);
	return 0;
}