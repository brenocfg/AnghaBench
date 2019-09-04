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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct pp_ctx {TYPE_1__ timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; struct ntb_dev* ntb; } ;
struct ntb_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct pp_ctx* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pp_ctx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_timer_func ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pp_ctx *pp_create_data(struct ntb_dev *ntb)
{
	struct pp_ctx *pp;

	pp = devm_kzalloc(&ntb->dev, sizeof(*pp), GFP_KERNEL);
	if (!pp)
		return ERR_PTR(-ENOMEM);

	pp->ntb = ntb;
	atomic_set(&pp->count, 0);
	spin_lock_init(&pp->lock);
	hrtimer_init(&pp->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	pp->timer.function = pp_timer_func;

	return pp;
}