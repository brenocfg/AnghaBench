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
struct TYPE_3__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RAsm ;

/* Variables and functions */
 int r_num_math (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int getnum(RAsm *a, const char *s) {
	if (!s) {
		return 0;
	}
	if (*s == '$') {
		s++;
	}
	return r_num_math (a->num, s);
}