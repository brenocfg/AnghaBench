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
typedef  int /*<<< orphan*/  u64 ;
struct waiting_dir_move {int dummy; } ;
struct send_ctx {int dummy; } ;

/* Variables and functions */
 struct waiting_dir_move* get_waiting_dir_move (struct send_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_waiting_for_move(struct send_ctx *sctx, u64 ino)
{
	struct waiting_dir_move *entry = get_waiting_dir_move(sctx, ino);

	return entry != NULL;
}