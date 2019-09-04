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
struct TYPE_3__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  (* fprintf_func ) (int /*<<< orphan*/ ,char*,unsigned int) ;} ;
typedef  TYPE_1__ disassemble_info ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void
fput_const (unsigned num, disassemble_info *info)
{
	if ((int)num < 0) {
		(*info->fprintf_func) (info->stream, "-%x", -(int)num);
	} else {
		(*info->fprintf_func) (info->stream, "%x", num);
	}
}