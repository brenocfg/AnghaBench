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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RRegItem ;

/* Variables and functions */
 char* r_reg_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool isFlag (RRegItem *reg) {
	const char *type = r_reg_get_type (reg->type);

	if (!strcmp (type, "flg"))
		return true;
	return false;
}