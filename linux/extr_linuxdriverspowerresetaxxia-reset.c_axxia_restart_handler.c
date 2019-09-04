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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int EFUSE_READ_DONE ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  RSTCTL_RST_CHIP ; 
 int /*<<< orphan*/  SC_CRIT_WRITE_KEY ; 
 int /*<<< orphan*/  SC_EFUSE_INT_STATUS ; 
 int /*<<< orphan*/  SC_LATCH_ON_RESET ; 
 int /*<<< orphan*/  SC_RESET_CONTROL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syscon ; 

__attribute__((used)) static int axxia_restart_handler(struct notifier_block *this,
				 unsigned long mode, void *cmd)
{
	/* Access Key (0xab) */
	regmap_write(syscon, SC_CRIT_WRITE_KEY, 0xab);
	/* Select internal boot from 0xffff0000 */
	regmap_write(syscon, SC_LATCH_ON_RESET, 0x00000040);
	/* Assert ResetReadDone (to avoid hanging in boot ROM) */
	regmap_write(syscon, SC_EFUSE_INT_STATUS, EFUSE_READ_DONE);
	/* Assert chip reset */
	regmap_update_bits(syscon, SC_RESET_CONTROL,
			   RSTCTL_RST_CHIP, RSTCTL_RST_CHIP);

	return NOTIFY_DONE;
}