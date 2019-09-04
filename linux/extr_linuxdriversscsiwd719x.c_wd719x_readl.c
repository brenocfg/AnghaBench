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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wd719x {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static inline u32 wd719x_readl(struct wd719x *wd, u8 reg)
{
	return ioread32(wd->base + reg);
}