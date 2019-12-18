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
struct snd_ad1843 {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  chip; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct ad1843_bitfield {int nbits; int lo_bit; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad1843_write_bits(struct snd_ad1843 *ad1843,
			     const struct ad1843_bitfield *field,
			     int newval)
{
	int w, mask, oldval, newbits;

	w = ad1843->read(ad1843->chip, field->reg);
	mask = ((1 << field->nbits) - 1) << field->lo_bit;
	oldval = (w & mask) >> field->lo_bit;
	newbits = (newval << field->lo_bit) & mask;
	w = (w & ~mask) | newbits;
	ad1843->write(ad1843->chip, field->reg, w);

	return oldval;
}