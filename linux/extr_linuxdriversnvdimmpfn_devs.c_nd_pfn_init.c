#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
typedef  scalar_t__ u32 ;
struct nd_region {int /*<<< orphan*/  dev; scalar_t__ ro; } ;
struct nd_pfn_sb {void* checksum; void* align; void* end_trunc; void* start_pad; void* version_minor; void* version_major; int /*<<< orphan*/  parent_uuid; int /*<<< orphan*/  uuid; int /*<<< orphan*/  signature; void* npfns; void* dataoff; void* mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct nd_pfn {scalar_t__ mode; scalar_t__ align; char const* uuid; TYPE_2__ dev; struct nd_pfn_sb* pfn_sb; struct nd_namespace_common* ndns; } ;
struct TYPE_6__ {scalar_t__ start; } ;
struct nd_namespace_io {TYPE_1__ res; } ;
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
struct nd_gen_sb {int dummy; } ;
typedef  scalar_t__ resource_size_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 char* DAX_SIG ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PFN_MODE_PMEM ; 
 scalar_t__ PFN_MODE_RAM ; 
 unsigned long PFN_SECTION_ALIGN_UP (scalar_t__) ; 
 char* PFN_SIG ; 
 int PFN_SIG_LEN ; 
 int /*<<< orphan*/  PMD_SIZE ; 
 scalar_t__ SZ_128K ; 
 scalar_t__ SZ_4K ; 
 scalar_t__ SZ_8K ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 void* cpu_to_le64 (unsigned long) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct nd_pfn_sb* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_nd_dax (TYPE_2__*) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct nd_pfn_sb*,int /*<<< orphan*/ ,int) ; 
 char const* nd_dev_to_uuid (int /*<<< orphan*/ *) ; 
 int nd_pfn_validate (struct nd_pfn*,char const*) ; 
 unsigned long nd_sb_checksum (struct nd_gen_sb*) ; 
 int nvdimm_write_bytes (struct nd_namespace_common*,scalar_t__,struct nd_pfn_sb*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_size (TYPE_1__*) ; 
 struct nd_namespace_io* to_nd_namespace_io (int /*<<< orphan*/ *) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trim_pfn_device (struct nd_pfn*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int nd_pfn_init(struct nd_pfn *nd_pfn)
{
	u32 dax_label_reserve = is_nd_dax(&nd_pfn->dev) ? SZ_128K : 0;
	struct nd_namespace_common *ndns = nd_pfn->ndns;
	struct nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	resource_size_t start, size;
	struct nd_region *nd_region;
	u32 start_pad, end_trunc;
	struct nd_pfn_sb *pfn_sb;
	unsigned long npfns;
	phys_addr_t offset;
	const char *sig;
	u64 checksum;
	int rc;

	pfn_sb = devm_kzalloc(&nd_pfn->dev, sizeof(*pfn_sb), GFP_KERNEL);
	if (!pfn_sb)
		return -ENOMEM;

	nd_pfn->pfn_sb = pfn_sb;
	if (is_nd_dax(&nd_pfn->dev))
		sig = DAX_SIG;
	else
		sig = PFN_SIG;
	rc = nd_pfn_validate(nd_pfn, sig);
	if (rc != -ENODEV)
		return rc;

	/* no info block, do init */;
	nd_region = to_nd_region(nd_pfn->dev.parent);
	if (nd_region->ro) {
		dev_info(&nd_pfn->dev,
				"%s is read-only, unable to init metadata\n",
				dev_name(&nd_region->dev));
		return -ENXIO;
	}

	memset(pfn_sb, 0, sizeof(*pfn_sb));

	trim_pfn_device(nd_pfn, &start_pad, &end_trunc);
	if (start_pad + end_trunc)
		dev_info(&nd_pfn->dev, "%s alignment collision, truncate %d bytes\n",
				dev_name(&ndns->dev), start_pad + end_trunc);

	/*
	 * Note, we use 64 here for the standard size of struct page,
	 * debugging options may cause it to be larger in which case the
	 * implementation will limit the pfns advertised through
	 * ->direct_access() to those that are included in the memmap.
	 */
	start = nsio->res.start + start_pad;
	size = resource_size(&nsio->res);
	npfns = PFN_SECTION_ALIGN_UP((size - start_pad - end_trunc - SZ_8K)
			/ PAGE_SIZE);
	if (nd_pfn->mode == PFN_MODE_PMEM) {
		/*
		 * The altmap should be padded out to the block size used
		 * when populating the vmemmap. This *should* be equal to
		 * PMD_SIZE for most architectures.
		 */
		offset = ALIGN(start + SZ_8K + 64 * npfns + dax_label_reserve,
				max(nd_pfn->align, PMD_SIZE)) - start;
	} else if (nd_pfn->mode == PFN_MODE_RAM)
		offset = ALIGN(start + SZ_8K + dax_label_reserve,
				nd_pfn->align) - start;
	else
		return -ENXIO;

	if (offset + start_pad + end_trunc >= size) {
		dev_err(&nd_pfn->dev, "%s unable to satisfy requested alignment\n",
				dev_name(&ndns->dev));
		return -ENXIO;
	}

	npfns = (size - offset - start_pad - end_trunc) / SZ_4K;
	pfn_sb->mode = cpu_to_le32(nd_pfn->mode);
	pfn_sb->dataoff = cpu_to_le64(offset);
	pfn_sb->npfns = cpu_to_le64(npfns);
	memcpy(pfn_sb->signature, sig, PFN_SIG_LEN);
	memcpy(pfn_sb->uuid, nd_pfn->uuid, 16);
	memcpy(pfn_sb->parent_uuid, nd_dev_to_uuid(&ndns->dev), 16);
	pfn_sb->version_major = cpu_to_le16(1);
	pfn_sb->version_minor = cpu_to_le16(2);
	pfn_sb->start_pad = cpu_to_le32(start_pad);
	pfn_sb->end_trunc = cpu_to_le32(end_trunc);
	pfn_sb->align = cpu_to_le32(nd_pfn->align);
	checksum = nd_sb_checksum((struct nd_gen_sb *) pfn_sb);
	pfn_sb->checksum = cpu_to_le64(checksum);

	return nvdimm_write_bytes(ndns, SZ_4K, pfn_sb, sizeof(*pfn_sb), 0);
}