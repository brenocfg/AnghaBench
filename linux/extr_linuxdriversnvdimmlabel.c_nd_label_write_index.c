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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct nvdimm_drvdata {int ns_next; int ns_current; } ;
struct nd_namespace_index {int labelsize; void* myoff; void* checksum; int /*<<< orphan*/ * free; void* minor; void* major; void* nslot; void* labeloff; void* otheroff; void* mysize; void* seq; int /*<<< orphan*/  flags; int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BITS_PER_LONG ; 
 unsigned long ND_NSINDEX_INIT ; 
 int /*<<< orphan*/  NSINDEX_SIGNATURE ; 
 int /*<<< orphan*/  NSINDEX_SIG_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (int) ; 
 void* __cpu_to_le64 (unsigned long) ; 
 int __le32_to_cpu (void*) ; 
 int /*<<< orphan*/  __le64_to_cpu (void*) ; 
 int /*<<< orphan*/  clear_bit_le (int,unsigned long*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 unsigned long nd_fletcher64 (struct nd_namespace_index*,unsigned long,int) ; 
 scalar_t__ nd_label_base (struct nvdimm_drvdata*) ; 
 int /*<<< orphan*/  nd_label_copy (struct nvdimm_drvdata*,int /*<<< orphan*/ ,struct nd_namespace_index*) ; 
 int nd_label_next_nsindex (int) ; 
 int nvdimm_num_label_slots (struct nvdimm_drvdata*) ; 
 int nvdimm_set_config_data (struct nvdimm_drvdata*,int /*<<< orphan*/ ,struct nd_namespace_index*,unsigned long) ; 
 unsigned long sizeof_namespace_index (struct nvdimm_drvdata*) ; 
 int sizeof_namespace_label (struct nvdimm_drvdata*) ; 
 int /*<<< orphan*/  to_current_namespace_index (struct nvdimm_drvdata*) ; 
 struct nd_namespace_index* to_namespace_index (struct nvdimm_drvdata*,int) ; 

__attribute__((used)) static int nd_label_write_index(struct nvdimm_drvdata *ndd, int index, u32 seq,
		unsigned long flags)
{
	struct nd_namespace_index *nsindex;
	unsigned long offset;
	u64 checksum;
	u32 nslot;
	int rc;

	nsindex = to_namespace_index(ndd, index);
	if (flags & ND_NSINDEX_INIT)
		nslot = nvdimm_num_label_slots(ndd);
	else
		nslot = __le32_to_cpu(nsindex->nslot);

	memcpy(nsindex->sig, NSINDEX_SIGNATURE, NSINDEX_SIG_LEN);
	memset(&nsindex->flags, 0, 3);
	nsindex->labelsize = sizeof_namespace_label(ndd) >> 8;
	nsindex->seq = __cpu_to_le32(seq);
	offset = (unsigned long) nsindex
		- (unsigned long) to_namespace_index(ndd, 0);
	nsindex->myoff = __cpu_to_le64(offset);
	nsindex->mysize = __cpu_to_le64(sizeof_namespace_index(ndd));
	offset = (unsigned long) to_namespace_index(ndd,
			nd_label_next_nsindex(index))
		- (unsigned long) to_namespace_index(ndd, 0);
	nsindex->otheroff = __cpu_to_le64(offset);
	offset = (unsigned long) nd_label_base(ndd)
		- (unsigned long) to_namespace_index(ndd, 0);
	nsindex->labeloff = __cpu_to_le64(offset);
	nsindex->nslot = __cpu_to_le32(nslot);
	nsindex->major = __cpu_to_le16(1);
	if (sizeof_namespace_label(ndd) < 256)
		nsindex->minor = __cpu_to_le16(1);
	else
		nsindex->minor = __cpu_to_le16(2);
	nsindex->checksum = __cpu_to_le64(0);
	if (flags & ND_NSINDEX_INIT) {
		unsigned long *free = (unsigned long *) nsindex->free;
		u32 nfree = ALIGN(nslot, BITS_PER_LONG);
		int last_bits, i;

		memset(nsindex->free, 0xff, nfree / 8);
		for (i = 0, last_bits = nfree - nslot; i < last_bits; i++)
			clear_bit_le(nslot + i, free);
	}
	checksum = nd_fletcher64(nsindex, sizeof_namespace_index(ndd), 1);
	nsindex->checksum = __cpu_to_le64(checksum);
	rc = nvdimm_set_config_data(ndd, __le64_to_cpu(nsindex->myoff),
			nsindex, sizeof_namespace_index(ndd));
	if (rc < 0)
		return rc;

	if (flags & ND_NSINDEX_INIT)
		return 0;

	/* copy the index we just wrote to the new 'next' */
	WARN_ON(index != ndd->ns_next);
	nd_label_copy(ndd, to_current_namespace_index(ndd), nsindex);
	ndd->ns_current = nd_label_next_nsindex(ndd->ns_current);
	ndd->ns_next = nd_label_next_nsindex(ndd->ns_next);
	WARN_ON(ndd->ns_current == ndd->ns_next);

	return 0;
}