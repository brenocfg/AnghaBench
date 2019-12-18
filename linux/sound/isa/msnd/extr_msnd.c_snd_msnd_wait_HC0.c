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
struct snd_msnd {unsigned int io; } ;

/* Variables and functions */
 int EIO ; 
 int HPCVR_HC ; 
 scalar_t__ HP_CVR ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static int snd_msnd_wait_HC0(struct snd_msnd *dev)
{
	unsigned int io = dev->io;
	int timeout = 1000;

	while (timeout-- > 0)
		if (!(inb(io + HP_CVR) & HPCVR_HC))
			return 0;

	return -EIO;
}