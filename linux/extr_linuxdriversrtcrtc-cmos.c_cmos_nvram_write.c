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
struct cmos_rtc {unsigned int day_alrm; unsigned int mon_alrm; unsigned int century; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMOS_WRITE (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ NVRAM_OFFSET ; 
 scalar_t__ can_bank2 ; 
 int /*<<< orphan*/  cmos_write_bank2 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmos_nvram_write(void *priv, unsigned int off, void *val,
			    size_t count)
{
	struct cmos_rtc	*cmos = priv;
	unsigned char	*buf = val;
	int		retval;

	/* NOTE:  on at least PCs and Ataris, the boot firmware uses a
	 * checksum on part of the NVRAM data.  That's currently ignored
	 * here.  If userspace is smart enough to know what fields of
	 * NVRAM to update, updating checksums is also part of its job.
	 */
	off += NVRAM_OFFSET;
	spin_lock_irq(&rtc_lock);
	for (retval = 0; count; count--, off++, retval++) {
		/* don't trash RTC registers */
		if (off == cmos->day_alrm
				|| off == cmos->mon_alrm
				|| off == cmos->century)
			buf++;
		else if (off < 128)
			CMOS_WRITE(*buf++, off);
		else if (can_bank2)
			cmos_write_bank2(*buf++, off);
		else
			break;
	}
	spin_unlock_irq(&rtc_lock);

	return retval;
}