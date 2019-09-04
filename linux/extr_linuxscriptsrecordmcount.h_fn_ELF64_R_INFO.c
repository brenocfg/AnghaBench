#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf_Rel ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_R_INFO (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  _w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fn_ELF_R_INFO(Elf_Rel *const rp, unsigned sym, unsigned type)
{
	rp->r_info = _w(ELF_R_INFO(sym, type));
}