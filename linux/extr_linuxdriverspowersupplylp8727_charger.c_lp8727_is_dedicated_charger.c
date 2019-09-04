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
 int LP8727_DCPORT ; 
 int /*<<< orphan*/  LP8727_STATUS1 ; 
 int /*<<< orphan*/  lp8727_read_byte (struct lp8727_chg*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lp8727_is_dedicated_charger(struct lp8727_chg *pchg)
{
	u8 val;

	lp8727_read_byte(pchg, LP8727_STATUS1, &val);
	return val & LP8727_DCPORT;
}