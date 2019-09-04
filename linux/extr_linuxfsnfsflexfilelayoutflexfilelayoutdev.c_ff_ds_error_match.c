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
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct nfs4_ff_layout_ds_err {scalar_t__ opnum; scalar_t__ status; scalar_t__ offset; int /*<<< orphan*/  length; int /*<<< orphan*/  deviceid; TYPE_1__ stateid; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pnfs_end_offset (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ff_ds_error_match(const struct nfs4_ff_layout_ds_err *e1,
		const struct nfs4_ff_layout_ds_err *e2)
{
	int ret;

	if (e1->opnum != e2->opnum)
		return e1->opnum < e2->opnum ? -1 : 1;
	if (e1->status != e2->status)
		return e1->status < e2->status ? -1 : 1;
	ret = memcmp(e1->stateid.data, e2->stateid.data,
			sizeof(e1->stateid.data));
	if (ret != 0)
		return ret;
	ret = memcmp(&e1->deviceid, &e2->deviceid, sizeof(e1->deviceid));
	if (ret != 0)
		return ret;
	if (pnfs_end_offset(e1->offset, e1->length) < e2->offset)
		return -1;
	if (e1->offset > pnfs_end_offset(e2->offset, e2->length))
		return 1;
	/* If ranges overlap or are contiguous, they are the same */
	return 0;
}