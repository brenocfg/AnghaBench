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
struct ucsi_ppm {int dummy; } ;
struct ucsi {int /*<<< orphan*/  work; struct ucsi_ppm* ppm; struct device* dev; int /*<<< orphan*/  ppm_lock; int /*<<< orphan*/  complete; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ucsi* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct ucsi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_long_wq ; 
 int /*<<< orphan*/  ucsi_init ; 

struct ucsi *ucsi_register_ppm(struct device *dev, struct ucsi_ppm *ppm)
{
	struct ucsi *ucsi;

	ucsi = kzalloc(sizeof(*ucsi), GFP_KERNEL);
	if (!ucsi)
		return ERR_PTR(-ENOMEM);

	INIT_WORK(&ucsi->work, ucsi_init);
	init_completion(&ucsi->complete);
	mutex_init(&ucsi->ppm_lock);

	ucsi->dev = dev;
	ucsi->ppm = ppm;

	/*
	 * Communication with the PPM takes a lot of time. It is not reasonable
	 * to initialize the driver here. Using a work for now.
	 */
	queue_work(system_long_wq, &ucsi->work);

	return ucsi;
}