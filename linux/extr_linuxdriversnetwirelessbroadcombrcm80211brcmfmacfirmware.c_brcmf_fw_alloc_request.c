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
typedef  size_t u32 ;
struct brcmf_fw_request {size_t n_items; TYPE_1__* items; } ;
struct brcmf_fw_name {char* extension; int /*<<< orphan*/  path; } ;
struct brcmf_fw_item {int dummy; } ;
struct brcmf_firmware_mapping {size_t chipid; int revmask; char* fw_base; } ;
typedef  int /*<<< orphan*/  chipname ;
struct TYPE_4__ {char* firmware_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int /*<<< orphan*/  BRCMF_FW_ALTPATH_LEN ; 
 int /*<<< orphan*/  BRCMF_FW_NAME_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brcmf_chip_name (size_t,size_t,char*,int) ; 
 int /*<<< orphan*/  brcmf_err (char*,size_t,size_t) ; 
 int /*<<< orphan*/  brcmf_info (char*,char*,char*) ; 
 TYPE_2__ brcmf_mp_global ; 
 struct brcmf_fw_request* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 size_t strnlen (char const*,int /*<<< orphan*/ ) ; 

struct brcmf_fw_request *
brcmf_fw_alloc_request(u32 chip, u32 chiprev,
		       const struct brcmf_firmware_mapping mapping_table[],
		       u32 table_size, struct brcmf_fw_name *fwnames,
		       u32 n_fwnames)
{
	struct brcmf_fw_request *fwreq;
	char chipname[12];
	const char *mp_path;
	size_t mp_path_len;
	u32 i, j;
	char end = '\0';
	size_t reqsz;

	for (i = 0; i < table_size; i++) {
		if (mapping_table[i].chipid == chip &&
		    mapping_table[i].revmask & BIT(chiprev))
			break;
	}

	if (i == table_size) {
		brcmf_err("Unknown chipid %d [%d]\n", chip, chiprev);
		return NULL;
	}

	reqsz = sizeof(*fwreq) + n_fwnames * sizeof(struct brcmf_fw_item);
	fwreq = kzalloc(reqsz, GFP_KERNEL);
	if (!fwreq)
		return NULL;

	brcmf_chip_name(chip, chiprev, chipname, sizeof(chipname));

	brcmf_info("using %s for chip %s\n",
		   mapping_table[i].fw_base, chipname);

	mp_path = brcmf_mp_global.firmware_path;
	mp_path_len = strnlen(mp_path, BRCMF_FW_ALTPATH_LEN);
	if (mp_path_len)
		end = mp_path[mp_path_len - 1];

	fwreq->n_items = n_fwnames;

	for (j = 0; j < n_fwnames; j++) {
		fwreq->items[j].path = fwnames[j].path;
		/* check if firmware path is provided by module parameter */
		if (brcmf_mp_global.firmware_path[0] != '\0') {
			strlcpy(fwnames[j].path, mp_path,
				BRCMF_FW_NAME_LEN);

			if (end != '/') {
				strlcat(fwnames[j].path, "/",
					BRCMF_FW_NAME_LEN);
			}
		}
		strlcat(fwnames[j].path, mapping_table[i].fw_base,
			BRCMF_FW_NAME_LEN);
		strlcat(fwnames[j].path, fwnames[j].extension,
			BRCMF_FW_NAME_LEN);
		fwreq->items[j].path = fwnames[j].path;
	}

	return fwreq;
}