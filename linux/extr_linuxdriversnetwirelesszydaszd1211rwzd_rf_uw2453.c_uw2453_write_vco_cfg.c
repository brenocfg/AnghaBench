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
typedef  int u16 ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_RV_BITS ; 
 int /*<<< orphan*/  UW2453_REGWRITE (int,int) ; 
 int zd_rfwrite_locked (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uw2453_write_vco_cfg(struct zd_chip *chip, u16 value)
{
	/* vendor driver always sets these upper bits even though the specs say
	 * they are reserved */
	u32 val = 0x40000 | value;
	return zd_rfwrite_locked(chip, UW2453_REGWRITE(3, val), RF_RV_BITS);
}