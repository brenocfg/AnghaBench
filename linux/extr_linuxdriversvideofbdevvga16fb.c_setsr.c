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
 int /*<<< orphan*/  VGA_GFX_D ; 
 int /*<<< orphan*/  VGA_GFX_SR_ENABLE ; 
 int vga_io_rgfx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_io_w (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int setsr(int sr)
{
	int oldsr;

	oldsr = vga_io_rgfx(VGA_GFX_SR_ENABLE);
	vga_io_w(VGA_GFX_D, sr);
	return oldsr;
}