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
struct ath79_spi {unsigned int rrw_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndelay (unsigned int) ; 

__attribute__((used)) static inline void ath79_spi_delay(struct ath79_spi *sp, unsigned int nsecs)
{
	if (nsecs > sp->rrw_delay)
		ndelay(nsecs - sp->rrw_delay);
}