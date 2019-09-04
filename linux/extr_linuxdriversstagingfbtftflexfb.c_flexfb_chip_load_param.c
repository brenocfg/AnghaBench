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
struct flexfb_lcd_controller {int /*<<< orphan*/  init_seq_sz; int /*<<< orphan*/  init_seq; scalar_t__ regwidth; int /*<<< orphan*/  setaddrwin; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 scalar_t__ height ; 
 int /*<<< orphan*/  init_num ; 
 int /*<<< orphan*/  initp ; 
 int /*<<< orphan*/  initp_num ; 
 scalar_t__ regwidth ; 
 int /*<<< orphan*/  setaddrwin ; 
 scalar_t__ width ; 

__attribute__((used)) static void flexfb_chip_load_param(const struct flexfb_lcd_controller *chip)
{
	if (!width)
		width = chip->width;
	if (!height)
		height = chip->height;
	setaddrwin = chip->setaddrwin;
	if (chip->regwidth)
		regwidth = chip->regwidth;
	if (!init_num) {
		initp = chip->init_seq;
		initp_num = chip->init_seq_sz;
	}
}