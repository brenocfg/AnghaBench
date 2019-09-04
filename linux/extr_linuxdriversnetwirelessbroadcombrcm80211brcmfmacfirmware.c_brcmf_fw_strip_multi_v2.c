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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct nvram_parser {int nvram_len; scalar_t__* nvram; int boardrev_found; } ;
typedef  int /*<<< orphan*/  prefix ;

/* Variables and functions */
 int BRCMF_FW_NVRAM_PCIEDEV_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (scalar_t__*,char*,int) ; 

__attribute__((used)) static void brcmf_fw_strip_multi_v2(struct nvram_parser *nvp, u16 domain_nr,
				    u16 bus_nr)
{
	char prefix[BRCMF_FW_NVRAM_PCIEDEV_LEN];
	size_t len;
	u32 i, j;
	u8 *nvram;

	nvram = kzalloc(nvp->nvram_len + 1 + 3 + sizeof(u32), GFP_KERNEL);
	if (!nvram)
		goto fail;

	/* Copy all valid entries, release old nvram and assign new one.
	 * Valid entries are of type pcie/X/Y/ where X = domain_nr and
	 * Y = bus_nr.
	 */
	snprintf(prefix, sizeof(prefix), "pcie/%d/%d/", domain_nr, bus_nr);
	len = strlen(prefix);
	i = 0;
	j = 0;
	while (i < nvp->nvram_len - len) {
		if (strncmp(&nvp->nvram[i], prefix, len) == 0) {
			i += len;
			if (strncmp(&nvp->nvram[i], "boardrev", 8) == 0)
				nvp->boardrev_found = true;
			while (nvp->nvram[i] != 0) {
				nvram[j] = nvp->nvram[i];
				i++;
				j++;
			}
			nvram[j] = 0;
			j++;
		}
		while (nvp->nvram[i] != 0)
			i++;
		i++;
	}
	kfree(nvp->nvram);
	nvp->nvram = nvram;
	nvp->nvram_len = j;
	return;
fail:
	kfree(nvram);
	nvp->nvram_len = 0;
}