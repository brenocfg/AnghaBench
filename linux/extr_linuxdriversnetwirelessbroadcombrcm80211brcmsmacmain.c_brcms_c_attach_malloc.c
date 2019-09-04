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
typedef  int uint ;
struct modulecb {int dummy; } ;
struct macstat {int dummy; } ;
struct brcms_stf {int dummy; } ;
struct brcms_pub {int dummy; } ;
struct brcms_protection {int dummy; } ;
struct brcms_hw_band {int dummy; } ;
struct brcms_hardware {int dummy; } ;
struct brcms_core {int dummy; } ;
struct brcms_c_info {TYPE_3__* corestate; struct brcms_band** bandstate; int /*<<< orphan*/ * stf; int /*<<< orphan*/ * protection; int /*<<< orphan*/ * bsscfg; int /*<<< orphan*/ * default_bss; int /*<<< orphan*/ * modulecb; TYPE_2__* hw; TYPE_1__* pub; } ;
struct brcms_bss_info {int dummy; } ;
struct brcms_band {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * macstat_snapshot; } ;
struct TYPE_5__ {struct brcms_hw_band** bandstate; struct brcms_c_info* wlc; } ;
struct TYPE_4__ {struct brcms_c_info* wlc; } ;

/* Variables and functions */
 int BRCMS_MAXMODULES ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAXBANDS ; 
 int /*<<< orphan*/ * brcms_c_bsscfg_malloc (int) ; 
 int /*<<< orphan*/  brcms_c_detach_mfree (struct brcms_c_info*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct brcms_c_info *
brcms_c_attach_malloc(uint unit, uint *err, uint devid)
{
	struct brcms_c_info *wlc;

	wlc = kzalloc(sizeof(struct brcms_c_info), GFP_ATOMIC);
	if (wlc == NULL) {
		*err = 1002;
		goto fail;
	}

	/* allocate struct brcms_c_pub state structure */
	wlc->pub = kzalloc(sizeof(struct brcms_pub), GFP_ATOMIC);
	if (wlc->pub == NULL) {
		*err = 1003;
		goto fail;
	}
	wlc->pub->wlc = wlc;

	/* allocate struct brcms_hardware state structure */

	wlc->hw = kzalloc(sizeof(struct brcms_hardware), GFP_ATOMIC);
	if (wlc->hw == NULL) {
		*err = 1005;
		goto fail;
	}
	wlc->hw->wlc = wlc;

	wlc->hw->bandstate[0] =
		kcalloc(MAXBANDS, sizeof(struct brcms_hw_band), GFP_ATOMIC);
	if (wlc->hw->bandstate[0] == NULL) {
		*err = 1006;
		goto fail;
	} else {
		int i;

		for (i = 1; i < MAXBANDS; i++)
			wlc->hw->bandstate[i] = (struct brcms_hw_band *)
			    ((unsigned long)wlc->hw->bandstate[0] +
			     (sizeof(struct brcms_hw_band) * i));
	}

	wlc->modulecb =
		kcalloc(BRCMS_MAXMODULES, sizeof(struct modulecb),
			GFP_ATOMIC);
	if (wlc->modulecb == NULL) {
		*err = 1009;
		goto fail;
	}

	wlc->default_bss = kzalloc(sizeof(struct brcms_bss_info), GFP_ATOMIC);
	if (wlc->default_bss == NULL) {
		*err = 1010;
		goto fail;
	}

	wlc->bsscfg = brcms_c_bsscfg_malloc(unit);
	if (wlc->bsscfg == NULL) {
		*err = 1011;
		goto fail;
	}

	wlc->protection = kzalloc(sizeof(struct brcms_protection),
				  GFP_ATOMIC);
	if (wlc->protection == NULL) {
		*err = 1016;
		goto fail;
	}

	wlc->stf = kzalloc(sizeof(struct brcms_stf), GFP_ATOMIC);
	if (wlc->stf == NULL) {
		*err = 1017;
		goto fail;
	}

	wlc->bandstate[0] =
		kcalloc(MAXBANDS, sizeof(struct brcms_band), GFP_ATOMIC);
	if (wlc->bandstate[0] == NULL) {
		*err = 1025;
		goto fail;
	} else {
		int i;

		for (i = 1; i < MAXBANDS; i++)
			wlc->bandstate[i] = (struct brcms_band *)
				((unsigned long)wlc->bandstate[0]
				+ (sizeof(struct brcms_band)*i));
	}

	wlc->corestate = kzalloc(sizeof(struct brcms_core), GFP_ATOMIC);
	if (wlc->corestate == NULL) {
		*err = 1026;
		goto fail;
	}

	wlc->corestate->macstat_snapshot =
		kzalloc(sizeof(struct macstat), GFP_ATOMIC);
	if (wlc->corestate->macstat_snapshot == NULL) {
		*err = 1027;
		goto fail;
	}

	return wlc;

 fail:
	brcms_c_detach_mfree(wlc);
	return NULL;
}