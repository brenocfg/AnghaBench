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
struct iss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap4iss_csi2_cleanup (struct iss_device*) ; 
 int omap4iss_csi2_init (struct iss_device*) ; 
 int omap4iss_csiphy_init (struct iss_device*) ; 
 int /*<<< orphan*/  omap4iss_ipipe_cleanup (struct iss_device*) ; 
 int omap4iss_ipipe_init (struct iss_device*) ; 
 int /*<<< orphan*/  omap4iss_ipipeif_cleanup (struct iss_device*) ; 
 int omap4iss_ipipeif_init (struct iss_device*) ; 
 int omap4iss_resizer_init (struct iss_device*) ; 

__attribute__((used)) static int iss_initialize_modules(struct iss_device *iss)
{
	int ret;

	ret = omap4iss_csiphy_init(iss);
	if (ret < 0) {
		dev_err(iss->dev, "CSI PHY initialization failed\n");
		goto error_csiphy;
	}

	ret = omap4iss_csi2_init(iss);
	if (ret < 0) {
		dev_err(iss->dev, "CSI2 initialization failed\n");
		goto error_csi2;
	}

	ret = omap4iss_ipipeif_init(iss);
	if (ret < 0) {
		dev_err(iss->dev, "ISP IPIPEIF initialization failed\n");
		goto error_ipipeif;
	}

	ret = omap4iss_ipipe_init(iss);
	if (ret < 0) {
		dev_err(iss->dev, "ISP IPIPE initialization failed\n");
		goto error_ipipe;
	}

	ret = omap4iss_resizer_init(iss);
	if (ret < 0) {
		dev_err(iss->dev, "ISP RESIZER initialization failed\n");
		goto error_resizer;
	}

	return 0;

error_resizer:
	omap4iss_ipipe_cleanup(iss);
error_ipipe:
	omap4iss_ipipeif_cleanup(iss);
error_ipipeif:
	omap4iss_csi2_cleanup(iss);
error_csi2:
error_csiphy:
	return ret;
}