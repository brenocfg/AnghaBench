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
typedef  int u32 ;
struct mtk_pinctrl {int /*<<< orphan*/  dev; } ;
struct mtk_pin_reg_calc {int nranges; struct mtk_pin_field_calc* range; } ;
struct mtk_pin_field_calc {int s_pin; int e_pin; int s_bit; int x_bits; int x_addrs; scalar_t__ s_addr; } ;
struct mtk_pin_field {int bitpos; int mask; int next; scalar_t__ offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mtk_hw_pin_field_lookup(struct mtk_pinctrl *hw, int pin,
				   const struct mtk_pin_reg_calc *rc,
				   struct mtk_pin_field *pfd)
{
	const struct mtk_pin_field_calc *c, *e;
	u32 bits;

	c = rc->range;
	e = c + rc->nranges;

	while (c < e) {
		if (pin >= c->s_pin && pin <= c->e_pin)
			break;
		c++;
	}

	if (c >= e) {
		dev_err(hw->dev, "Out of range for pin = %d\n", pin);
		return -EINVAL;
	}

	/* Caculated bits as the overall offset the pin is located at */
	bits = c->s_bit + (pin - c->s_pin) * (c->x_bits);

	/* Fill pfd from bits and 32-bit register applied is assumed */
	pfd->offset = c->s_addr + c->x_addrs * (bits / 32);
	pfd->bitpos = bits % 32;
	pfd->mask = (1 << c->x_bits) - 1;

	/* pfd->next is used for indicating that bit wrapping-around happens
	 * which requires the manipulation for bit 0 starting in the next
	 * register to form the complete field read/write.
	 */
	pfd->next = pfd->bitpos + c->x_bits - 1 > 31 ? c->x_addrs : 0;

	return 0;
}