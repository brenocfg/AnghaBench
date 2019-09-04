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
struct greybus_bundle_id {int dummy; } ;
struct gbphy_host {int /*<<< orphan*/  devices; struct gb_bundle* bundle; } ;
struct gbphy_device {int /*<<< orphan*/  list; } ;
struct gb_bundle {int num_cports; int /*<<< orphan*/ * cport_desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct gbphy_device*) ; 
 int PTR_ERR (struct gbphy_device*) ; 
 struct gbphy_device* gb_gbphy_create_dev (struct gb_bundle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_gbphy_disconnect (struct gb_bundle*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gbphy_host*) ; 
 struct gbphy_host* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_gbphy_probe(struct gb_bundle *bundle,
			  const struct greybus_bundle_id *id)
{
	struct gbphy_host *gbphy_host;
	struct gbphy_device *gbphy_dev;
	int i;

	if (bundle->num_cports == 0)
		return -ENODEV;

	gbphy_host = kzalloc(sizeof(*gbphy_host), GFP_KERNEL);
	if (!gbphy_host)
		return -ENOMEM;

	gbphy_host->bundle = bundle;
	INIT_LIST_HEAD(&gbphy_host->devices);
	greybus_set_drvdata(bundle, gbphy_host);

	/*
	 * Create a bunch of children devices, one per cport, and bind the
	 * bridged phy drivers to them.
	 */
	for (i = 0; i < bundle->num_cports; ++i) {
		gbphy_dev = gb_gbphy_create_dev(bundle, &bundle->cport_desc[i]);
		if (IS_ERR(gbphy_dev)) {
			gb_gbphy_disconnect(bundle);
			return PTR_ERR(gbphy_dev);
		}
		list_add(&gbphy_dev->list, &gbphy_host->devices);
	}

	gb_pm_runtime_put_autosuspend(bundle);

	return 0;
}