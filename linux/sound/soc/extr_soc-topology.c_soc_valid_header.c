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
struct soc_tplg {int pass; int /*<<< orphan*/  dev; TYPE_1__* fw; } ;
struct snd_soc_tplg_hdr {scalar_t__ size; scalar_t__ type; scalar_t__ magic; scalar_t__ abi; scalar_t__ payload_size; int /*<<< orphan*/  vendor_type; int /*<<< orphan*/  version; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_TPLG_ABI_VERSION ; 
 int SND_SOC_TPLG_ABI_VERSION_MIN ; 
 int SND_SOC_TPLG_MAGIC ; 
 scalar_t__ SOC_TPLG_MAGIC_BIG_ENDIAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  soc_tplg_get_hdr_offset (struct soc_tplg*) ; 

__attribute__((used)) static int soc_valid_header(struct soc_tplg *tplg,
	struct snd_soc_tplg_hdr *hdr)
{
	if (soc_tplg_get_hdr_offset(tplg) >= tplg->fw->size)
		return 0;

	if (le32_to_cpu(hdr->size) != sizeof(*hdr)) {
		dev_err(tplg->dev,
			"ASoC: invalid header size for type %d at offset 0x%lx size 0x%zx.\n",
			le32_to_cpu(hdr->type), soc_tplg_get_hdr_offset(tplg),
			tplg->fw->size);
		return -EINVAL;
	}

	/* big endian firmware objects not supported atm */
	if (hdr->magic == SOC_TPLG_MAGIC_BIG_ENDIAN) {
		dev_err(tplg->dev,
			"ASoC: pass %d big endian not supported header got %x at offset 0x%lx size 0x%zx.\n",
			tplg->pass, hdr->magic,
			soc_tplg_get_hdr_offset(tplg), tplg->fw->size);
		return -EINVAL;
	}

	if (le32_to_cpu(hdr->magic) != SND_SOC_TPLG_MAGIC) {
		dev_err(tplg->dev,
			"ASoC: pass %d does not have a valid header got %x at offset 0x%lx size 0x%zx.\n",
			tplg->pass, hdr->magic,
			soc_tplg_get_hdr_offset(tplg), tplg->fw->size);
		return -EINVAL;
	}

	/* Support ABI from version 4 */
	if (le32_to_cpu(hdr->abi) > SND_SOC_TPLG_ABI_VERSION ||
	    le32_to_cpu(hdr->abi) < SND_SOC_TPLG_ABI_VERSION_MIN) {
		dev_err(tplg->dev,
			"ASoC: pass %d invalid ABI version got 0x%x need 0x%x at offset 0x%lx size 0x%zx.\n",
			tplg->pass, hdr->abi,
			SND_SOC_TPLG_ABI_VERSION, soc_tplg_get_hdr_offset(tplg),
			tplg->fw->size);
		return -EINVAL;
	}

	if (hdr->payload_size == 0) {
		dev_err(tplg->dev, "ASoC: header has 0 size at offset 0x%lx.\n",
			soc_tplg_get_hdr_offset(tplg));
		return -EINVAL;
	}

	if (tplg->pass == le32_to_cpu(hdr->type))
		dev_dbg(tplg->dev,
			"ASoC: Got 0x%x bytes of type %d version %d vendor %d at pass %d\n",
			hdr->payload_size, hdr->type, hdr->version,
			hdr->vendor_type, tplg->pass);

	return 1;
}