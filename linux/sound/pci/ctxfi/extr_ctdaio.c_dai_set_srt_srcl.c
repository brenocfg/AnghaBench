#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rsc {TYPE_2__* ops; } ;
struct dai {int /*<<< orphan*/  ctrl_blk; TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* index ) (struct rsc*) ;int /*<<< orphan*/  (* master ) (struct rsc*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* dai_srt_set_srcm ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rsc*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct rsc*) ; 

__attribute__((used)) static int dai_set_srt_srcl(struct dai *dai, struct rsc *src)
{
	src->ops->master(src);
	dai->hw->dai_srt_set_srcm(dai->ctrl_blk, src->ops->index(src));
	return 0;
}