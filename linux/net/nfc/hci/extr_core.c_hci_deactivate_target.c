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
typedef  int /*<<< orphan*/  u8 ;
struct nfc_target {int dummy; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void hci_deactivate_target(struct nfc_dev *nfc_dev,
				  struct nfc_target *target,
				  u8 mode)
{
}