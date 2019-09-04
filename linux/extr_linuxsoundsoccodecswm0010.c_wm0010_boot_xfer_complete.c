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
typedef  int /*<<< orphan*/  u32 ;
struct wm0010_priv {int pll_running; scalar_t__ boot_failed; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * rx_buf; } ;
struct TYPE_3__ {scalar_t__ status; } ;
struct wm0010_boot_xfer {scalar_t__ done; TYPE_2__ t; TYPE_1__ m; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM0010_STAGE2 ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct wm0010_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm0010_mark_boot_failure (struct wm0010_priv*) ; 

__attribute__((used)) static void wm0010_boot_xfer_complete(void *data)
{
	struct wm0010_boot_xfer *xfer = data;
	struct snd_soc_component *component = xfer->component;
	struct wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	u32 *out32 = xfer->t.rx_buf;
	int i;

	if (xfer->m.status != 0) {
		dev_err(component->dev, "SPI transfer failed: %d\n",
			xfer->m.status);
		wm0010_mark_boot_failure(wm0010);
		if (xfer->done)
			complete(xfer->done);
		return;
	}

	for (i = 0; i < xfer->t.len / 4; i++) {
		dev_dbg(component->dev, "%d: %04x\n", i, out32[i]);

		switch (be32_to_cpu(out32[i])) {
		case 0xe0e0e0e0:
			dev_err(component->dev,
				"%d: ROM error reported in stage 2\n", i);
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x55555555:
			if (wm0010->state < WM0010_STAGE2)
				break;
			dev_err(component->dev,
				"%d: ROM bootloader running in stage 2\n", i);
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x0fed0000:
			dev_dbg(component->dev, "Stage2 loader running\n");
			break;

		case 0x0fed0007:
			dev_dbg(component->dev, "CODE_HDR packet received\n");
			break;

		case 0x0fed0008:
			dev_dbg(component->dev, "CODE_DATA packet received\n");
			break;

		case 0x0fed0009:
			dev_dbg(component->dev, "Download complete\n");
			break;

		case 0x0fed000c:
			dev_dbg(component->dev, "Application start\n");
			break;

		case 0x0fed000e:
			dev_dbg(component->dev, "PLL packet received\n");
			wm0010->pll_running = true;
			break;

		case 0x0fed0025:
			dev_err(component->dev, "Device reports image too long\n");
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x0fed002c:
			dev_err(component->dev, "Device reports bad SPI packet\n");
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x0fed0031:
			dev_err(component->dev, "Device reports SPI read overflow\n");
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x0fed0032:
			dev_err(component->dev, "Device reports SPI underclock\n");
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x0fed0033:
			dev_err(component->dev, "Device reports bad header packet\n");
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x0fed0034:
			dev_err(component->dev, "Device reports invalid packet type\n");
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x0fed0035:
			dev_err(component->dev, "Device reports data before header error\n");
			wm0010_mark_boot_failure(wm0010);
			break;

		case 0x0fed0038:
			dev_err(component->dev, "Device reports invalid PLL packet\n");
			break;

		case 0x0fed003a:
			dev_err(component->dev, "Device reports packet alignment error\n");
			wm0010_mark_boot_failure(wm0010);
			break;

		default:
			dev_err(component->dev, "Unrecognised return 0x%x\n",
			    be32_to_cpu(out32[i]));
			wm0010_mark_boot_failure(wm0010);
			break;
		}

		if (wm0010->boot_failed)
			break;
	}

	if (xfer->done)
		complete(xfer->done);
}