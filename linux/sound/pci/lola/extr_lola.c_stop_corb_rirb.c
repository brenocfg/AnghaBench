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
struct lola {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR0 ; 
 int /*<<< orphan*/  CORBCTL ; 
 int /*<<< orphan*/  RIRBCTL ; 
 int /*<<< orphan*/  lola_writeb (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_corb_rirb(struct lola *chip)
{
	/* disable ringbuffer DMAs */
	lola_writeb(chip, BAR0, RIRBCTL, 0);
	lola_writeb(chip, BAR0, CORBCTL, 0);
}