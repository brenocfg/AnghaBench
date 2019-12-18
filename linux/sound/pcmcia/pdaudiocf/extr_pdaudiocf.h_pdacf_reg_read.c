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
struct snd_pdacf {scalar_t__ port; } ;

/* Variables and functions */
 unsigned short inw (scalar_t__) ; 

__attribute__((used)) static inline unsigned short pdacf_reg_read(struct snd_pdacf *chip, unsigned char reg)
{
	return inw(chip->port + reg);
}