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
struct xway_gphy_priv {int /*<<< orphan*/  fw_name; } ;
struct firmware {size_t size; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,size_t) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* PTR_ALIGN (void*,size_t) ; 
 size_t XRX200_GPHY_FW_ALIGN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dmam_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static int xway_gphy_load(struct device *dev, struct xway_gphy_priv *priv,
			  dma_addr_t *dev_addr)
{
	const struct firmware *fw;
	void *fw_addr;
	dma_addr_t dma_addr;
	size_t size;
	int ret;

	ret = request_firmware(&fw, priv->fw_name, dev);
	if (ret) {
		dev_err(dev, "failed to load firmware: %s, error: %i\n",
			priv->fw_name, ret);
		return ret;
	}

	/*
	 * GPHY cores need the firmware code in a persistent and contiguous
	 * memory area with a 16 kB boundary aligned start address.
	 */
	size = fw->size + XRX200_GPHY_FW_ALIGN;

	fw_addr = dmam_alloc_coherent(dev, size, &dma_addr, GFP_KERNEL);
	if (fw_addr) {
		fw_addr = PTR_ALIGN(fw_addr, XRX200_GPHY_FW_ALIGN);
		*dev_addr = ALIGN(dma_addr, XRX200_GPHY_FW_ALIGN);
		memcpy(fw_addr, fw->data, fw->size);
	} else {
		dev_err(dev, "failed to alloc firmware memory\n");
		ret = -ENOMEM;
	}

	release_firmware(fw);

	return ret;
}