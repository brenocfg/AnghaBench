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
struct module {int /*<<< orphan*/  taints; } ;
struct TYPE_2__ {char c_true; scalar_t__ module; } ;

/* Variables and functions */
 int TAINT_FLAGS_COUNT ; 
 TYPE_1__* taint_flags ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t module_flags_taint(struct module *mod, char *buf)
{
	size_t l = 0;
	int i;

	for (i = 0; i < TAINT_FLAGS_COUNT; i++) {
		if (taint_flags[i].module && test_bit(i, &mod->taints))
			buf[l++] = taint_flags[i].c_true;
	}

	return l;
}