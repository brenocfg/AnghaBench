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
struct vsc7385 {TYPE_1__* pdata; struct spi_device* spi; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct firmware {int size; scalar_t__ data; } ;
struct TYPE_2__ {char* ucode_name; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_SYSTEM ; 
 int /*<<< orphan*/  VSC73XX_ICPU_SRAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int vsc7385_icpu_reset (struct vsc7385*) ; 
 int vsc7385_icpu_start (struct vsc7385*) ; 
 int vsc7385_icpu_stop (struct vsc7385*) ; 
 int vsc7385_read (struct vsc7385*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int vsc7385_write (struct vsc7385*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc7385_upload_ucode(struct vsc7385 *vsc)
{
	struct spi_device *spi = vsc->spi;
	const struct firmware *firmware;
	char *ucode_name;
	unsigned char *dp;
	unsigned int curVal;
	int i;
	int diffs;
	int rc;

	ucode_name = (vsc->pdata->ucode_name) ? vsc->pdata->ucode_name
					      : "vsc7385_ucode.bin";
	rc = request_firmware(&firmware, ucode_name, &spi->dev);
	if (rc) {
		dev_err(&spi->dev, "request_firmware failed, err=%d\n",
			rc);
		return rc;
	}

	rc = vsc7385_icpu_stop(vsc);
	if (rc)
		goto out;

	rc = vsc7385_icpu_reset(vsc);
	if (rc)
		goto out;

	dev_info(&spi->dev, "uploading microcode...\n");

	dp = (unsigned char *) firmware->data;
	for (i = 0; i < firmware->size; i++) {
		rc = vsc7385_write(vsc, VSC73XX_BLOCK_SYSTEM, 0,
				   VSC73XX_ICPU_SRAM, *dp++);
		if (rc) {
			dev_err(&spi->dev, "could not load microcode, err=%d\n",
				rc);
			goto out;
		}
	}

	rc = vsc7385_icpu_reset(vsc);
	if (rc)
		goto out;

	dev_info(&spi->dev, "verifying microcode...\n");

	dp = (unsigned char *) firmware->data;
	diffs = 0;
	for (i = 0; i < firmware->size; i++) {
		rc = vsc7385_read(vsc, VSC73XX_BLOCK_SYSTEM, 0,
				  VSC73XX_ICPU_SRAM, &curVal);
		if (rc) {
			dev_err(&spi->dev, "could not read microcode %d\n",
				rc);
			goto out;
		}

		if (curVal > 0xff) {
			dev_err(&spi->dev, "bad val read: %04x : %02x  %02x\n",
				i, *dp, curVal);
			rc = -EIO;
			goto out;
		}

		if ((curVal & 0xff) != *dp) {
			diffs++;
			dev_err(&spi->dev, "verify error: %04x : %02x  %02x\n",
				i, *dp, curVal);

			if (diffs > 4)
				break;
			}
		dp++;
	}

	if (diffs) {
		dev_err(&spi->dev, "microcode verification failed\n");
		rc = -EIO;
		goto out;
	}

	dev_info(&spi->dev, "microcode uploaded\n");

	rc = vsc7385_icpu_start(vsc);

out:
	release_firmware(firmware);
	return rc;
}