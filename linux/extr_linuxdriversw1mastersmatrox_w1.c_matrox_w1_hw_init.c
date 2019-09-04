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
struct matrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MATROX_GET_CONTROL ; 
 int /*<<< orphan*/  MATROX_GET_DATA ; 
 int /*<<< orphan*/  matrox_w1_write_reg (struct matrox_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void matrox_w1_hw_init(struct matrox_device *dev)
{
	matrox_w1_write_reg(dev, MATROX_GET_DATA, 0xFF);
	matrox_w1_write_reg(dev, MATROX_GET_CONTROL, 0x00);
}