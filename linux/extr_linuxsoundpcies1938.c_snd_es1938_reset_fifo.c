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
struct es1938 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  SLSB_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_es1938_reset_fifo(struct es1938 *chip)
{
	outb(2, SLSB_REG(chip, RESET));
	outb(0, SLSB_REG(chip, RESET));
}