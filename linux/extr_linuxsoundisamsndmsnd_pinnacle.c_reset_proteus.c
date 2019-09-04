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
struct snd_msnd {scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPPRORESET_OFF ; 
 int /*<<< orphan*/  HPPRORESET_ON ; 
 scalar_t__ HP_PROR ; 
 int /*<<< orphan*/  TIME_PRO_RESET ; 
 int /*<<< orphan*/  TIME_PRO_RESET_DONE ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void reset_proteus(struct snd_msnd *chip)
{
	outb(HPPRORESET_ON, chip->io + HP_PROR);
	msleep(TIME_PRO_RESET);
	outb(HPPRORESET_OFF, chip->io + HP_PROR);
	msleep(TIME_PRO_RESET_DONE);
}