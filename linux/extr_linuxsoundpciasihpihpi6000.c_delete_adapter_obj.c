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
struct hpi_hw_obj {scalar_t__ dw2040_HPICSR; int /*<<< orphan*/  p_cache; } ;
struct hpi_adapter_obj {scalar_t__ has_control_cache; struct hpi_hw_obj* priv; } ;

/* Variables and functions */
 scalar_t__ HPI_RESET ; 
 int /*<<< orphan*/  hpi_free_control_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct hpi_hw_obj*) ; 

__attribute__((used)) static void delete_adapter_obj(struct hpi_adapter_obj *pao)
{
	struct hpi_hw_obj *phw = pao->priv;

	if (pao->has_control_cache)
		hpi_free_control_cache(phw->p_cache);

	/* reset DSPs on adapter */
	iowrite32(0x0003000F, phw->dw2040_HPICSR + HPI_RESET);

	kfree(phw);
}