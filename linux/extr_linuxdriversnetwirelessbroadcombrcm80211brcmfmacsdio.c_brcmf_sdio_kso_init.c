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
typedef  int u8 ;
struct brcmf_sdio {int /*<<< orphan*/  sdiodev; struct brcmf_core* sdio_core; } ;
struct brcmf_core {int rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBSDIO_FUNC1_SLEEPCSR ; 
 int SBSDIO_FUNC1_SLEEPCSR_KSO_EN ; 
 int SBSDIO_FUNC1_SLEEPCSR_KSO_MASK ; 
 int SBSDIO_FUNC1_SLEEPCSR_KSO_SHIFT ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int brcmf_sdiod_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int brcmf_sdio_kso_init(struct brcmf_sdio *bus)
{
	struct brcmf_core *core = bus->sdio_core;
	u8 val;
	int err = 0;

	brcmf_dbg(TRACE, "Enter\n");

	/* KSO bit added in SDIO core rev 12 */
	if (core->rev < 12)
		return 0;

	val = brcmf_sdiod_readb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR, &err);
	if (err) {
		brcmf_err("error reading SBSDIO_FUNC1_SLEEPCSR\n");
		return err;
	}

	if (!(val & SBSDIO_FUNC1_SLEEPCSR_KSO_MASK)) {
		val |= (SBSDIO_FUNC1_SLEEPCSR_KSO_EN <<
			SBSDIO_FUNC1_SLEEPCSR_KSO_SHIFT);
		brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_FUNC1_SLEEPCSR,
				   val, &err);
		if (err) {
			brcmf_err("error writing SBSDIO_FUNC1_SLEEPCSR\n");
			return err;
		}
	}

	return 0;
}