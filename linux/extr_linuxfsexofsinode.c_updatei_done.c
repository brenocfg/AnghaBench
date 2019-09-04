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
struct updatei_args {TYPE_1__* sbi; } ;
struct ore_io_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_curr_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct updatei_args*) ; 
 int /*<<< orphan*/  ore_put_io_state (struct ore_io_state*) ; 

__attribute__((used)) static void updatei_done(struct ore_io_state *ios, void *p)
{
	struct updatei_args *args = p;

	ore_put_io_state(ios);

	atomic_dec(&args->sbi->s_curr_pending);

	kfree(args);
}