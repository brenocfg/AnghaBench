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
 unsigned int LOLA_DSD_STS_BCIS ; 
 unsigned int LOLA_DSD_STS_DESE ; 
 int /*<<< orphan*/  STS ; 
 unsigned int lola_dsd_read (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lola_dsd_write (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void lola_stream_clear_pending_irq(struct lola *chip,
					  struct lola_stream *str)
{
	unsigned int val = lola_dsd_read(chip, str->dsd, STS);
	val &= LOLA_DSD_STS_DESE | LOLA_DSD_STS_BCIS;
	if (val)
		lola_dsd_write(chip, str->dsd, STS, val);
}