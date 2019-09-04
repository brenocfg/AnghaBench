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
typedef  int /*<<< orphan*/  guid_t ;
typedef  enum nvdimm_claim_class { ____Placeholder_nvdimm_claim_class } nvdimm_claim_class ;

/* Variables and functions */
 int NVDIMM_CCLASS_BTT ; 
 int NVDIMM_CCLASS_BTT2 ; 
 int NVDIMM_CCLASS_DAX ; 
 int NVDIMM_CCLASS_NONE ; 
 int NVDIMM_CCLASS_PFN ; 
 int NVDIMM_CCLASS_UNKNOWN ; 
 scalar_t__ guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guid_null ; 
 int /*<<< orphan*/  nvdimm_btt2_guid ; 
 int /*<<< orphan*/  nvdimm_btt_guid ; 
 int /*<<< orphan*/  nvdimm_dax_guid ; 
 int /*<<< orphan*/  nvdimm_pfn_guid ; 

enum nvdimm_claim_class to_nvdimm_cclass(guid_t *guid)
{
	if (guid_equal(guid, &nvdimm_btt_guid))
		return NVDIMM_CCLASS_BTT;
	else if (guid_equal(guid, &nvdimm_btt2_guid))
		return NVDIMM_CCLASS_BTT2;
	else if (guid_equal(guid, &nvdimm_pfn_guid))
		return NVDIMM_CCLASS_PFN;
	else if (guid_equal(guid, &nvdimm_dax_guid))
		return NVDIMM_CCLASS_DAX;
	else if (guid_equal(guid, &guid_null))
		return NVDIMM_CCLASS_NONE;

	return NVDIMM_CCLASS_UNKNOWN;
}