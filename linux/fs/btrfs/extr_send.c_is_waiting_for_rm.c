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
struct send_ctx {int dummy; } ;
struct orphan_dir_info {int dummy; } ;

/* Variables and functions */
 struct orphan_dir_info* get_orphan_dir_info (struct send_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_waiting_for_rm(struct send_ctx *sctx, u64 dir_ino)
{
	struct orphan_dir_info *odi = get_orphan_dir_info(sctx, dir_ino);

	return odi != NULL;
}