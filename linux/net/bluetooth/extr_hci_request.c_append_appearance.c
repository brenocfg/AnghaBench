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
struct hci_dev {int /*<<< orphan*/  appearance; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIR_APPEARANCE ; 
 int /*<<< orphan*/  eir_append_le16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 append_appearance(struct hci_dev *hdev, u8 *ptr, u8 ad_len)
{
	return eir_append_le16(ptr, ad_len, EIR_APPEARANCE, hdev->appearance);
}