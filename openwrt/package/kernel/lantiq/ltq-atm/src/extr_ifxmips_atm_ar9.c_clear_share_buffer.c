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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_REG_W32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SB_RAM0_ADDR (int /*<<< orphan*/ ) ; 
 unsigned int SB_RAM0_DWLEN ; 
 unsigned int SB_RAM1_DWLEN ; 
 unsigned int SB_RAM2_DWLEN ; 
 unsigned int SB_RAM3_DWLEN ; 
 unsigned int SB_RAM4_DWLEN ; 

__attribute__((used)) static inline void clear_share_buffer(void)
{
    volatile u32 *p = SB_RAM0_ADDR(0);
    unsigned int i;

    for ( i = 0; i < SB_RAM0_DWLEN + SB_RAM1_DWLEN + SB_RAM2_DWLEN + SB_RAM3_DWLEN + SB_RAM4_DWLEN; i++ )
        IFX_REG_W32(0, p++);
}