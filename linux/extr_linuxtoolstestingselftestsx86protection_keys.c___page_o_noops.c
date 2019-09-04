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

__attribute__((used)) static inline void __page_o_noops(void)
{
	/* 8-bytes of instruction * 512 bytes = 1 page */
	asm(".rept 512 ; nopl 0x7eeeeeee(%eax) ; .endr");
}