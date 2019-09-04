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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct nvdimm_drvdata {int /*<<< orphan*/  dev; } ;
struct nd_namespace_label {void* checksum; void* rawsize; void* dpa; int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int SZ_4K ; 
 void* __cpu_to_le64 (int) ; 
 scalar_t__ __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int __le64_to_cpu (void*) ; 
 int /*<<< orphan*/  checksum ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 scalar_t__ namespace_label_has (struct nvdimm_drvdata*,int /*<<< orphan*/ ) ; 
 int nd_fletcher64 (struct nd_namespace_label*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sizeof_namespace_label (struct nvdimm_drvdata*) ; 

__attribute__((used)) static bool slot_valid(struct nvdimm_drvdata *ndd,
		struct nd_namespace_label *nd_label, u32 slot)
{
	/* check that we are written where we expect to be written */
	if (slot != __le32_to_cpu(nd_label->slot))
		return false;

	/* check that DPA allocations are page aligned */
	if ((__le64_to_cpu(nd_label->dpa)
				| __le64_to_cpu(nd_label->rawsize)) % SZ_4K)
		return false;

	/* check checksum */
	if (namespace_label_has(ndd, checksum)) {
		u64 sum, sum_save;

		sum_save = __le64_to_cpu(nd_label->checksum);
		nd_label->checksum = __cpu_to_le64(0);
		sum = nd_fletcher64(nd_label, sizeof_namespace_label(ndd), 1);
		nd_label->checksum = __cpu_to_le64(sum_save);
		if (sum != sum_save) {
			dev_dbg(ndd->dev, "fail checksum. slot: %d expect: %#llx\n",
				slot, sum);
			return false;
		}
	}

	return true;
}