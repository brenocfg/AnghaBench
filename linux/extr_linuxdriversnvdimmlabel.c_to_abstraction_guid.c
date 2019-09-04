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
typedef  int /*<<< orphan*/  const guid_t ;
typedef  enum nvdimm_claim_class { ____Placeholder_nvdimm_claim_class } nvdimm_claim_class ;

/* Variables and functions */
 int NVDIMM_CCLASS_BTT ; 
 int NVDIMM_CCLASS_BTT2 ; 
 int NVDIMM_CCLASS_DAX ; 
 int NVDIMM_CCLASS_PFN ; 
 int NVDIMM_CCLASS_UNKNOWN ; 
 int /*<<< orphan*/  const guid_null ; 
 int /*<<< orphan*/  const nvdimm_btt2_guid ; 
 int /*<<< orphan*/  const nvdimm_btt_guid ; 
 int /*<<< orphan*/  const nvdimm_dax_guid ; 
 int /*<<< orphan*/  const nvdimm_pfn_guid ; 

__attribute__((used)) static const guid_t *to_abstraction_guid(enum nvdimm_claim_class claim_class,
	guid_t *target)
{
	if (claim_class == NVDIMM_CCLASS_BTT)
		return &nvdimm_btt_guid;
	else if (claim_class == NVDIMM_CCLASS_BTT2)
		return &nvdimm_btt2_guid;
	else if (claim_class == NVDIMM_CCLASS_PFN)
		return &nvdimm_pfn_guid;
	else if (claim_class == NVDIMM_CCLASS_DAX)
		return &nvdimm_dax_guid;
	else if (claim_class == NVDIMM_CCLASS_UNKNOWN) {
		/*
		 * If we're modifying a namespace for which we don't
		 * know the claim_class, don't touch the existing guid.
		 */
		return target;
	} else
		return &guid_null;
}