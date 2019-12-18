#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  syntax; } ;
typedef  TYPE_1__ tms320_dasm_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCCCCCC ; 
 scalar_t__ field_valid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  field_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cond_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  substitute (int /*<<< orphan*/ ,char*,char*,...) ; 

void decode_cond(tms320_dasm_t * dasm)
{
	char tmp[64];

	if (field_valid (dasm, CCCCCCC)) {
		substitute (dasm->syntax, "cond", "%s", get_cond_str (field_value (dasm, CCCCCCC), tmp));
	}

	substitute(dasm->syntax, "[label, ]", "");
}