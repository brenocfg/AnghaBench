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
typedef  int /*<<< orphan*/  u8 ;
struct lp8727_chg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP8727_CHGDET_EN ; 
 int /*<<< orphan*/  LP8727_CTRL2 ; 
 int /*<<< orphan*/  lp8727_read_byte (struct lp8727_chg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lp8727_write_byte (struct lp8727_chg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp8727_enable_chgdet(struct lp8727_chg *pchg)
{
	u8 val;

	lp8727_read_byte(pchg, LP8727_CTRL2, &val);
	val |= LP8727_CHGDET_EN;
	lp8727_write_byte(pchg, LP8727_CTRL2, val);
}