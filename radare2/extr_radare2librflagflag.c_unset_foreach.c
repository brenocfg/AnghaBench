#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct unset_foreach_t {int /*<<< orphan*/  n; int /*<<< orphan*/  f; } ;
typedef  int /*<<< orphan*/  RFlagItem ;

/* Variables and functions */
 scalar_t__ IS_FI_NOTIN_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_flag_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool unset_foreach(RFlagItem *fi, void *user) {
	struct unset_foreach_t *u = (struct unset_foreach_t *)user;
	if (IS_FI_NOTIN_SPACE (u->f, fi)) {
		return true;
	}
	r_flag_unset (u->f, fi);
	u->n++;
	return true;
}