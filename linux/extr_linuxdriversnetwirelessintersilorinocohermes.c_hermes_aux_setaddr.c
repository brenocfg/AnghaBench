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
typedef  int /*<<< orphan*/  u16 ;
struct hermes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HERMES_AUXOFFSET ; 
 int /*<<< orphan*/  HERMES_AUXPAGE ; 
 int /*<<< orphan*/  hermes_write_reg (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
hermes_aux_setaddr(struct hermes *hw, u32 addr)
{
	hermes_write_reg(hw, HERMES_AUXPAGE, (u16) (addr >> 7));
	hermes_write_reg(hw, HERMES_AUXOFFSET, (u16) (addr & 0x7F));
}