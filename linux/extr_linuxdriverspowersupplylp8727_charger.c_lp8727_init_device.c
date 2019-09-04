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
typedef  int u8 ;
struct lp8727_chg {int dummy; } ;

/* Variables and functions */
 int LP8727_ADC_EN ; 
 int LP8727_CHGDET_EN ; 
 int LP8727_CP_EN ; 
 int /*<<< orphan*/  LP8727_CTRL1 ; 
 int /*<<< orphan*/  LP8727_CTRL2 ; 
 int LP8727_ID200_EN ; 
 int /*<<< orphan*/  LP8727_INT1 ; 
 int LP8727_INT_EN ; 
 int LP8788_NUM_INTREGS ; 
 int lp8727_read_bytes (struct lp8727_chg*,int /*<<< orphan*/ ,int*,int) ; 
 int lp8727_write_byte (struct lp8727_chg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lp8727_init_device(struct lp8727_chg *pchg)
{
	u8 val;
	int ret;
	u8 intstat[LP8788_NUM_INTREGS];

	/* clear interrupts */
	ret = lp8727_read_bytes(pchg, LP8727_INT1, intstat, LP8788_NUM_INTREGS);
	if (ret)
		return ret;

	val = LP8727_ID200_EN | LP8727_ADC_EN | LP8727_CP_EN;
	ret = lp8727_write_byte(pchg, LP8727_CTRL1, val);
	if (ret)
		return ret;

	val = LP8727_INT_EN | LP8727_CHGDET_EN;
	return lp8727_write_byte(pchg, LP8727_CTRL2, val);
}