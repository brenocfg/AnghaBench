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
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfc_targets_found (struct nfc_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

inline void nfc_driver_failure(struct nfc_dev *dev, int err)
{
	nfc_targets_found(dev, NULL, 0);
}