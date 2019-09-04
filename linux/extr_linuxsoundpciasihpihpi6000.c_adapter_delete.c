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
struct hpi_response {scalar_t__ error; } ;
struct hpi_message {int dummy; } ;
struct hpi_adapter_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_adapter_obj (struct hpi_adapter_obj*) ; 
 int /*<<< orphan*/  hpi_delete_adapter (struct hpi_adapter_obj*) ; 

__attribute__((used)) static void adapter_delete(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	delete_adapter_obj(pao);
	hpi_delete_adapter(pao);
	phr->error = 0;
}