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
struct icom_adapter {int /*<<< orphan*/  icom_adapter_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct icom_adapter*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icom_free_adapter(struct icom_adapter *icom_adapter)
{
	list_del(&icom_adapter->icom_adapter_entry);
	kfree(icom_adapter);
}