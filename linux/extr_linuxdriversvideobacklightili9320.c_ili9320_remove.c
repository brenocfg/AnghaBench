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
struct ili9320 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  ili9320_power (struct ili9320*,int /*<<< orphan*/ ) ; 

int ili9320_remove(struct ili9320 *ili)
{
	ili9320_power(ili, FB_BLANK_POWERDOWN);
	return 0;
}