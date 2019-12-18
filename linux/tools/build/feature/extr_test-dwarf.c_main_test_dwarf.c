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
typedef  int /*<<< orphan*/  Dwarf ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_C_READ ; 
 int /*<<< orphan*/ * dwarf_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void)
{
	Dwarf *dbg = dwarf_begin(0, DWARF_C_READ);

	return (long)dbg;
}