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
struct hpi_response {int dummy; } ;
struct hpi_message {size_t obj_index; } ;
struct hpi_hw_obj {int* flag_outstream_just_reset; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static void outstream_reset(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;
	phw->flag_outstream_just_reset[phm->obj_index] = 1;
	hw_message(pao, phm, phr);
}