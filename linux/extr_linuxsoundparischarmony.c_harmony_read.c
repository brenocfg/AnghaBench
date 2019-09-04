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
struct snd_harmony {unsigned int iobase; } ;

/* Variables and functions */
 unsigned long __raw_readl (unsigned int) ; 

__attribute__((used)) static inline unsigned long
harmony_read(struct snd_harmony *h, unsigned r)
{
	return __raw_readl(h->iobase + r);
}