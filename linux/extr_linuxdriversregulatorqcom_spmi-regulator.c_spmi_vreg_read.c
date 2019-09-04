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
typedef  scalar_t__ u16 ;
struct spmi_regulator {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int spmi_vreg_read(struct spmi_regulator *vreg, u16 addr, u8 *buf,
				 int len)
{
	return regmap_bulk_read(vreg->regmap, vreg->base + addr, buf, len);
}