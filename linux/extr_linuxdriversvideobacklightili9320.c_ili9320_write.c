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
struct ili9320 {int (* write ) (struct ili9320*,unsigned int,unsigned int) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int stub1 (struct ili9320*,unsigned int,unsigned int) ; 

int ili9320_write(struct ili9320 *ili, unsigned int reg, unsigned int value)
{
	dev_dbg(ili->dev, "write: reg=%02x, val=%04x\n", reg, value);
	return ili->write(ili, reg, value);
}