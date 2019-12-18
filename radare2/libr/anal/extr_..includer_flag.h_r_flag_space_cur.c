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
struct TYPE_3__ {int /*<<< orphan*/  spaces; } ;
typedef  int /*<<< orphan*/  RSpace ;
typedef  TYPE_1__ RFlag ;

/* Variables and functions */
 int /*<<< orphan*/ * r_spaces_current (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline RSpace *r_flag_space_cur(RFlag *f) {
	return r_spaces_current (&f->spaces);
}