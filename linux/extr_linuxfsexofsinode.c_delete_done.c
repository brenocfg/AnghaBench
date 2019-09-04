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
struct ore_io_state {int dummy; } ;
struct exofs_sb_info {int /*<<< orphan*/  s_curr_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ore_put_io_state (struct ore_io_state*) ; 

__attribute__((used)) static void delete_done(struct ore_io_state *ios, void *p)
{
	struct exofs_sb_info *sbi = p;

	ore_put_io_state(ios);

	atomic_dec(&sbi->s_curr_pending);
}