#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sdpid; int hauai; int wauai; } ;
struct TYPE_5__ {int qcode; int h; int w; int flags0; int l; } ;
struct raw3270_ua {TYPE_3__ aua; TYPE_2__ uab; } ;
struct TYPE_4__ {scalar_t__ rc; } ;
struct raw3270 {int* init_data; int model; int rows; int cols; int /*<<< orphan*/  flags; TYPE_1__ init_readmod; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAW3270_FLAGS_14BITADDR ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
raw3270_size_device(struct raw3270 *rp)
{
	struct raw3270_ua *uap;

	/* Got a Query Reply */
	uap = (struct raw3270_ua *) (rp->init_data + 1);
	/* Paranoia check. */
	if (rp->init_readmod.rc || rp->init_data[0] != 0x88 ||
	    uap->uab.qcode != 0x81) {
		/* Couldn't detect size. Use default model 2. */
		rp->model = 2;
		rp->rows = 24;
		rp->cols = 80;
		return;
	}
	/* Copy rows/columns of default Usable Area */
	rp->rows = uap->uab.h;
	rp->cols = uap->uab.w;
	/* Check for 14 bit addressing */
	if ((uap->uab.flags0 & 0x0d) == 0x01)
		set_bit(RAW3270_FLAGS_14BITADDR, &rp->flags);
	/* Check for Alternate Usable Area */
	if (uap->uab.l == sizeof(struct raw3270_ua) &&
	    uap->aua.sdpid == 0x02) {
		rp->rows = uap->aua.hauai;
		rp->cols = uap->aua.wauai;
	}
	/* Try to find a model. */
	rp->model = 0;
	if (rp->rows == 24 && rp->cols == 80)
		rp->model = 2;
	if (rp->rows == 32 && rp->cols == 80)
		rp->model = 3;
	if (rp->rows == 43 && rp->cols == 80)
		rp->model = 4;
	if (rp->rows == 27 && rp->cols == 132)
		rp->model = 5;
}