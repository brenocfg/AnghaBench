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
struct disassemble_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */

__attribute__((used)) static void memory_error_func(int status, bfd_vma memaddr, struct disassemble_info *info) {
	// --
}