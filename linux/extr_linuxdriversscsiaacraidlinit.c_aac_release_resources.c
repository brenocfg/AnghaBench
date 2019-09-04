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
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aac_adapter_disable_int (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_free_irq (struct aac_dev*) ; 

__attribute__((used)) static void aac_release_resources(struct aac_dev *aac)
{
	aac_adapter_disable_int(aac);
	aac_free_irq(aac);
}