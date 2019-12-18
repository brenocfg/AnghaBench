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
struct cmd_bind_section {int num_binds; TYPE_1__* binds; } ;
struct TYPE_2__ {int is_builtin; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bind_dealloc (TYPE_1__*) ; 

__attribute__((used)) static void remove_binds(struct cmd_bind_section *bs, bool builtin)
{
    for (int n = bs->num_binds - 1; n >= 0; n--) {
        if (bs->binds[n].is_builtin == builtin) {
            bind_dealloc(&bs->binds[n]);
            assert(bs->num_binds >= 1);
            bs->binds[n] = bs->binds[bs->num_binds - 1];
            bs->num_binds--;
        }
    }
}