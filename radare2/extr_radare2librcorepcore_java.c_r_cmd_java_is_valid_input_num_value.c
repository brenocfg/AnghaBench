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
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 scalar_t__ r_num_math (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int r_cmd_java_is_valid_input_num_value(RCore *core, const char *input_value){
	ut64 value = input_value ? r_num_math (core->num, input_value) : 0;
	return !(value == 0 && input_value && *input_value == '0');
}