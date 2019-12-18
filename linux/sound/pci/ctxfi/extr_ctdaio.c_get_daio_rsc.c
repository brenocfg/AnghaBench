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
struct daio {int dummy; } ;
struct dao {struct daio daio; } ;
struct daio_mgr {int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; int /*<<< orphan*/  (* commit_write ) (struct daio_mgr*) ;int /*<<< orphan*/  (* daio_enable ) (struct daio_mgr*,struct daio*) ;TYPE_1__* card; } ;
struct daio_desc {scalar_t__ type; } ;
struct dai {struct daio daio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DAIO_OUT_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dai_rsc_init (struct dao*,struct daio_desc const*,struct daio_mgr*) ; 
 int daio_mgr_get_rsc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  daio_mgr_put_rsc (int /*<<< orphan*/ *,scalar_t__) ; 
 int dao_rsc_init (struct dao*,struct daio_desc const*,struct daio_mgr*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct dao*) ; 
 struct dao* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct daio_mgr*,struct daio*) ; 
 int /*<<< orphan*/  stub2 (struct daio_mgr*) ; 

__attribute__((used)) static int get_daio_rsc(struct daio_mgr *mgr,
			const struct daio_desc *desc,
			struct daio **rdaio)
{
	int err;
	unsigned long flags;

	*rdaio = NULL;

	/* Check whether there are sufficient daio resources to meet request. */
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	err = daio_mgr_get_rsc(&mgr->mgr, desc->type);
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	if (err) {
		dev_err(mgr->card->dev,
			"Can't meet DAIO resource request!\n");
		return err;
	}

	err = -ENOMEM;
	/* Allocate mem for daio resource */
	if (desc->type <= DAIO_OUT_MAX) {
		struct dao *dao = kzalloc(sizeof(*dao), GFP_KERNEL);
		if (!dao)
			goto error;

		err = dao_rsc_init(dao, desc, mgr);
		if (err) {
			kfree(dao);
			goto error;
		}

		*rdaio = &dao->daio;
	} else {
		struct dai *dai = kzalloc(sizeof(*dai), GFP_KERNEL);
		if (!dai)
			goto error;

		err = dai_rsc_init(dai, desc, mgr);
		if (err) {
			kfree(dai);
			goto error;
		}

		*rdaio = &dai->daio;
	}

	mgr->daio_enable(mgr, *rdaio);
	mgr->commit_write(mgr);

	return 0;

error:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	daio_mgr_put_rsc(&mgr->mgr, desc->type);
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	return err;
}