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
struct lola_stream {int /*<<< orphan*/  dsd; } ;
struct lola {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL ; 
 unsigned int LOLA_DSD_CTL_DEIE ; 
 unsigned int LOLA_DSD_CTL_IOCE ; 
 unsigned int LOLA_DSD_CTL_SRUN ; 
 unsigned int LOLA_DSD_CTL_VLRCV ; 
 int /*<<< orphan*/  lola_dsd_write (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  lola_stream_clear_pending_irq (struct lola*,struct lola_stream*) ; 

__attribute__((used)) static void lola_stream_start(struct lola *chip, struct lola_stream *str,
			      unsigned int tstamp)
{
	lola_stream_clear_pending_irq(chip, str);
	lola_dsd_write(chip, str->dsd, CTL,
		       LOLA_DSD_CTL_SRUN |
		       LOLA_DSD_CTL_IOCE |
		       LOLA_DSD_CTL_DEIE |
		       LOLA_DSD_CTL_VLRCV |
		       tstamp);
}