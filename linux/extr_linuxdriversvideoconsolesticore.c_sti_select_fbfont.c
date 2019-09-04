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
struct sti_cooked_rom {int dummy; } ;
struct sti_cooked_font {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct sti_cooked_font *
sti_select_fbfont(struct sti_cooked_rom *cooked_rom, const char *fbfont_name)
{
	return NULL;
}