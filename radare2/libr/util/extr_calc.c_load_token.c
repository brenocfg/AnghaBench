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
struct TYPE_3__ {char const* calc_buf; int /*<<< orphan*/ * calc_err; int /*<<< orphan*/  calc_len; scalar_t__ calc_i; } ;
typedef  TYPE_1__ RNumCalc ;
typedef  int /*<<< orphan*/  RNum ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void load_token(RNum *num, RNumCalc *nc, const char *s) {
	nc->calc_i = 0;
	nc->calc_len = strlen (s);
	nc->calc_buf = s;
	nc->calc_err = NULL;
}