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
typedef  int /*<<< orphan*/  u64 ;
struct tool_ctx {int /*<<< orphan*/  db_wq; TYPE_1__* ntb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_read (TYPE_1__*) ; 
 int /*<<< orphan*/  ntb_db_vector_mask (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tool_db_event(void *ctx, int vec)
{
	struct tool_ctx *tc = ctx;
	u64 db_bits, db_mask;

	db_mask = ntb_db_vector_mask(tc->ntb, vec);
	db_bits = ntb_db_read(tc->ntb);

	dev_dbg(&tc->ntb->dev, "doorbell vec %d mask %#llx bits %#llx\n",
		vec, db_mask, db_bits);

	wake_up(&tc->db_wq);
}