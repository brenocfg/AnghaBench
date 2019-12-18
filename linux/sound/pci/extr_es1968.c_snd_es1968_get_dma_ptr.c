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
struct esschan {scalar_t__* base; int /*<<< orphan*/ * apu; } ;
struct es1968 {int dummy; } ;

/* Variables and functions */
 unsigned int apu_get_register (struct es1968*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned int
snd_es1968_get_dma_ptr(struct es1968 *chip, struct esschan *es)
{
	unsigned int offset;

	offset = apu_get_register(chip, es->apu[0], 5);

	offset -= es->base[0];

	return (offset & 0xFFFE);	/* hardware is in words */
}