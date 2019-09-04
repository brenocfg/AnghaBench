#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  clang_path; } ;

/* Variables and functions */
 int PATH_MAX ; 
 TYPE_1__ llvm_param ; 
 int search_program (int /*<<< orphan*/ ,char*,char*) ; 

int llvm__search_clang(void)
{
	char clang_path[PATH_MAX];

	return search_program(llvm_param.clang_path, "clang", clang_path);
}