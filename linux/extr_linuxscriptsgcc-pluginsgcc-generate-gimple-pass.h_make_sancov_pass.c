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
struct opt_pass {int dummy; } ;
struct TYPE_2__ {struct opt_pass pass; } ;

/* Variables and functions */
 TYPE_1__ _PASS_NAME_PASS ; 

struct opt_pass *_MAKE_PASS_NAME_PASS(void)
{
	return &_PASS_NAME_PASS.pass;
}