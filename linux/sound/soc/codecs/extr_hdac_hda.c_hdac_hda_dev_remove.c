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
struct TYPE_2__ {int /*<<< orphan*/  jackpoll_work; } ;
struct hdac_hda_priv {TYPE_1__ codec; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct hdac_hda_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdac_hda_dev_remove(struct hdac_device *hdev)
{
	struct hdac_hda_priv *hda_pvt;

	hda_pvt = dev_get_drvdata(&hdev->dev);
	cancel_delayed_work_sync(&hda_pvt->codec.jackpoll_work);
	return 0;
}