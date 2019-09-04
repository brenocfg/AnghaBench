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
struct gvp11_scsiregs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int check_wd33c93(struct gvp11_scsiregs *regs)
{
#ifdef CHECK_WD33C93
	volatile unsigned char *sasr_3393, *scmd_3393;
	unsigned char save_sasr;
	unsigned char q, qq;

	/*
	 * These darn GVP boards are a problem - it can be tough to tell
	 * whether or not they include a SCSI controller. This is the
	 * ultimate Yet-Another-GVP-Detection-Hack in that it actually
	 * probes for a WD33c93 chip: If we find one, it's extremely
	 * likely that this card supports SCSI, regardless of Product_
	 * Code, Board_Size, etc.
	 */

	/* Get pointers to the presumed register locations and save contents */

	sasr_3393 = &regs->SASR;
	scmd_3393 = &regs->SCMD;
	save_sasr = *sasr_3393;

	/* First test the AuxStatus Reg */

	q = *sasr_3393;	/* read it */
	if (q & 0x08)	/* bit 3 should always be clear */
		return -ENODEV;
	*sasr_3393 = WD_AUXILIARY_STATUS;	/* setup indirect address */
	if (*sasr_3393 == WD_AUXILIARY_STATUS) {	/* shouldn't retain the write */
		*sasr_3393 = save_sasr;	/* Oops - restore this byte */
		return -ENODEV;
	}
	if (*sasr_3393 != q) {	/* should still read the same */
		*sasr_3393 = save_sasr;	/* Oops - restore this byte */
		return -ENODEV;
	}
	if (*scmd_3393 != q)	/* and so should the image at 0x1f */
		return -ENODEV;

	/*
	 * Ok, we probably have a wd33c93, but let's check a few other places
	 * for good measure. Make sure that this works for both 'A and 'B
	 * chip versions.
	 */

	*sasr_3393 = WD_SCSI_STATUS;
	q = *scmd_3393;
	*sasr_3393 = WD_SCSI_STATUS;
	*scmd_3393 = ~q;
	*sasr_3393 = WD_SCSI_STATUS;
	qq = *scmd_3393;
	*sasr_3393 = WD_SCSI_STATUS;
	*scmd_3393 = q;
	if (qq != q)	/* should be read only */
		return -ENODEV;
	*sasr_3393 = 0x1e;	/* this register is unimplemented */
	q = *scmd_3393;
	*sasr_3393 = 0x1e;
	*scmd_3393 = ~q;
	*sasr_3393 = 0x1e;
	qq = *scmd_3393;
	*sasr_3393 = 0x1e;
	*scmd_3393 = q;
	if (qq != q || qq != 0xff)	/* should be read only, all 1's */
		return -ENODEV;
	*sasr_3393 = WD_TIMEOUT_PERIOD;
	q = *scmd_3393;
	*sasr_3393 = WD_TIMEOUT_PERIOD;
	*scmd_3393 = ~q;
	*sasr_3393 = WD_TIMEOUT_PERIOD;
	qq = *scmd_3393;
	*sasr_3393 = WD_TIMEOUT_PERIOD;
	*scmd_3393 = q;
	if (qq != (~q & 0xff))	/* should be read/write */
		return -ENODEV;
#endif /* CHECK_WD33C93 */

	return 0;
}