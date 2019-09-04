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
typedef  TYPE_1__ RFlag ;

/* Variables and functions */
 int r_spaces_rename (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static inline bool r_flag_space_rename(RFlag *f, const char *oname, const char *nname) {
	return r_spaces_rename (&f->spaces, oname, nname);
}