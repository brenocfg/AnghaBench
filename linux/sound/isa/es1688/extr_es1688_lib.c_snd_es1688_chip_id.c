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
struct snd_es1688 {scalar_t__ hardware; int version; } ;

/* Variables and functions */
 scalar_t__ ES1688_HW_688 ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static const char *snd_es1688_chip_id(struct snd_es1688 *chip)
{
	static char tmp[16];
	sprintf(tmp, "ES%s688 rev %i", chip->hardware == ES1688_HW_688 ? "" : "1", chip->version & 0x0f);
	return tmp;
}