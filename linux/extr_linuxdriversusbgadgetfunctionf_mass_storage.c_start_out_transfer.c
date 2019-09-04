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
struct fsg_common {TYPE_1__* fsg; } ;
struct fsg_buffhd {int /*<<< orphan*/  state; int /*<<< orphan*/  outreq; } ;
struct TYPE_2__ {int /*<<< orphan*/  bulk_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_STATE_FULL ; 
 int /*<<< orphan*/  BUF_STATE_RECEIVING ; 
 int /*<<< orphan*/  fsg_is_set (struct fsg_common*) ; 
 scalar_t__ start_transfer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool start_out_transfer(struct fsg_common *common, struct fsg_buffhd *bh)
{
	if (!fsg_is_set(common))
		return false;
	bh->state = BUF_STATE_RECEIVING;
	if (start_transfer(common->fsg, common->fsg->bulk_out, bh->outreq))
		bh->state = BUF_STATE_FULL;
	return true;
}