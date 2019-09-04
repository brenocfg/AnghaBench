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
struct clk {int dummy; } ;

/* Variables and functions */
 unsigned long S3C2410_WTCNT_MAXCNT ; 
 unsigned long S3C2410_WTCON_MAXDIV ; 
 int S3C2410_WTCON_PRESCALE_MAX ; 
 unsigned long clk_get_rate (struct clk*) ; 

__attribute__((used)) static inline unsigned int s3c2410wdt_max_timeout(struct clk *clock)
{
	unsigned long freq = clk_get_rate(clock);

	return S3C2410_WTCNT_MAXCNT / (freq / (S3C2410_WTCON_PRESCALE_MAX + 1)
				       / S3C2410_WTCON_MAXDIV);
}