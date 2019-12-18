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

/* Variables and functions */
 int /*<<< orphan*/  IFX_REG_W32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_IGU1_IER ; 
 int /*<<< orphan*/  MBOX_IGU1_ISRC ; 
 int /*<<< orphan*/  MBOX_IGU3_IER ; 
 int /*<<< orphan*/  MBOX_IGU3_ISRC ; 

__attribute__((used)) static inline void init_mailbox(void)
{
    IFX_REG_W32(0xFFFFFFFF, MBOX_IGU1_ISRC);
    IFX_REG_W32(0x00000000, MBOX_IGU1_IER);
    IFX_REG_W32(0xFFFFFFFF, MBOX_IGU3_ISRC);
    IFX_REG_W32(0x00000000, MBOX_IGU3_IER);
}