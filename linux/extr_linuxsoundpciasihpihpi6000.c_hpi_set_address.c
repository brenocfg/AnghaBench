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
typedef  scalar_t__ u32 ;
struct dsp_obj {int /*<<< orphan*/  prHPI_address; int /*<<< orphan*/  pa_parent_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  H6WRITE ; 
 scalar_t__ PCI_TIMEOUT ; 
 scalar_t__ hpi6000_check_PCI2040_error_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpi_set_address(struct dsp_obj *pdo, u32 address)
{
	u32 timeout = PCI_TIMEOUT;

	do {
		iowrite32(address, pdo->prHPI_address);
	} while (hpi6000_check_PCI2040_error_flag(pdo->pa_parent_adapter,
			H6WRITE)
		&& --timeout);

	if (timeout)
		return 0;

	return 1;
}