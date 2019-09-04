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
typedef  int /*<<< orphan*/  uint32_t ;
struct gxfb_par {scalar_t__ vid_regs; } ;

/* Variables and functions */
 scalar_t__ VP_FP_START ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline uint32_t read_fp(struct gxfb_par *par, int reg)
{
	return readl(par->vid_regs + 8*reg + VP_FP_START);
}