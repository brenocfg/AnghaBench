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
struct device {int dummy; } ;
struct brcmf_fw_request {int dummy; } ;
struct brcmf_fw_name {char const* member_0; int /*<<< orphan*/ * member_1; } ;
struct brcmf_bus {int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct brcmf_fw_name*) ; 
 int ENOMEM ; 
 struct brcmf_fw_request* brcmf_fw_alloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmf_fw_name*,int /*<<< orphan*/ ,struct brcmf_fw_name*,int /*<<< orphan*/ ) ; 
 struct brcmf_fw_name* brcmf_sdio_fwnames ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_fw_request*) ; 

__attribute__((used)) static
int brcmf_sdio_get_fwname(struct device *dev, const char *ext, u8 *fw_name)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_fw_request *fwreq;
	struct brcmf_fw_name fwnames[] = {
		{ ext, fw_name },
	};

	fwreq = brcmf_fw_alloc_request(bus_if->chip, bus_if->chiprev,
				       brcmf_sdio_fwnames,
				       ARRAY_SIZE(brcmf_sdio_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	if (!fwreq)
		return -ENOMEM;

	kfree(fwreq);
	return 0;
}