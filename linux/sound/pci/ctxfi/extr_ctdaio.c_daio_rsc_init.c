#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hw {int chip_type; } ;
struct daio_desc {size_t type; int /*<<< orphan*/  msr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; } ;
struct daio {scalar_t__ type; TYPE_1__ rscl; TYPE_1__ rscr; } ;
struct TYPE_7__ {unsigned int left; unsigned int right; } ;
struct TYPE_6__ {unsigned int left; unsigned int right; } ;

/* Variables and functions */
#define  ATC20K1 129 
#define  ATC20K2 128 
 int /*<<< orphan*/  DAIO ; 
 scalar_t__ DAIO_OUT_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  daio_in_rsc_ops_20k1 ; 
 int /*<<< orphan*/  daio_in_rsc_ops_20k2 ; 
 int /*<<< orphan*/  daio_out_rsc_ops ; 
 TYPE_4__* idx_20k1 ; 
 TYPE_3__* idx_20k2 ; 
 int rsc_init (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hw*) ; 
 int /*<<< orphan*/  rsc_uninit (TYPE_1__*) ; 

__attribute__((used)) static int daio_rsc_init(struct daio *daio,
			 const struct daio_desc *desc,
			 struct hw *hw)
{
	int err;
	unsigned int idx_l, idx_r;

	switch (hw->chip_type) {
	case ATC20K1:
		idx_l = idx_20k1[desc->type].left;
		idx_r = idx_20k1[desc->type].right;
		break;
	case ATC20K2:
		idx_l = idx_20k2[desc->type].left;
		idx_r = idx_20k2[desc->type].right;
		break;
	default:
		return -EINVAL;
	}
	err = rsc_init(&daio->rscl, idx_l, DAIO, desc->msr, hw);
	if (err)
		return err;

	err = rsc_init(&daio->rscr, idx_r, DAIO, desc->msr, hw);
	if (err)
		goto error1;

	/* Set daio->rscl/r->ops to daio specific ones */
	if (desc->type <= DAIO_OUT_MAX) {
		daio->rscl.ops = daio->rscr.ops = &daio_out_rsc_ops;
	} else {
		switch (hw->chip_type) {
		case ATC20K1:
			daio->rscl.ops = daio->rscr.ops = &daio_in_rsc_ops_20k1;
			break;
		case ATC20K2:
			daio->rscl.ops = daio->rscr.ops = &daio_in_rsc_ops_20k2;
			break;
		default:
			break;
		}
	}
	daio->type = desc->type;

	return 0;

error1:
	rsc_uninit(&daio->rscl);
	return err;
}