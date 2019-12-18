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
struct wireless_dev {TYPE_1__* conn; } ;
struct TYPE_2__ {struct TYPE_2__* ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void cfg80211_sme_free(struct wireless_dev *wdev)
{
	if (!wdev->conn)
		return;

	kfree(wdev->conn->ie);
	kfree(wdev->conn);
	wdev->conn = NULL;
}