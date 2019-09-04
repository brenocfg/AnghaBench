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
typedef  int /*<<< orphan*/  u16 ;
struct tps6598x {int dummy; } ;

/* Variables and functions */
 int tps6598x_block_write (struct tps6598x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int tps6598x_write16(struct tps6598x *tps, u8 reg, u16 val)
{
	return tps6598x_block_write(tps, reg, &val, sizeof(u16));
}