#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __printRecursive (TYPE_1__*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listFlag ; 
 int /*<<< orphan*/  r_flag_foreach_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_flag_space_cur (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __flag_graph (RCore *core, const char *input, int mode) {
	RList *flags = r_list_newf (NULL);
	r_flag_foreach_space (core->flags, r_flag_space_cur (core->flags), listFlag, flags);
	__printRecursive (core, flags, input, mode, 0);
	r_list_free (flags);
}