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
struct snd_rme9652 {scalar_t__ prev_hw_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void rme9652_reset_hw_pointer(struct snd_rme9652 *rme9652)
{
	int i;

	/* reset the FIFO pointer to zero. We do this by writing to 8
	   registers, each of which is a 32bit wide register, and set
	   them all to zero. Note that s->iobase is a pointer to
	   int32, not pointer to char.  
	*/

	for (i = 0; i < 8; i++) {
		rme9652_write(rme9652, i * 4, 0);
		udelay(10);
	}
	rme9652->prev_hw_offset = 0;
}