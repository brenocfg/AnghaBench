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
struct perf_sample {size_t raw_size; unsigned char* raw_data; } ;
struct cf_trailer_entry {int dummy; } ;
struct cf_ctrset_entry {void* res1; void* ctr; void* set; void* def; } ;

/* Variables and functions */
 void* be16_to_cpu (void*) ; 
 size_t ctrset_size (struct cf_ctrset_entry*) ; 
 int /*<<< orphan*/  ctrset_valid (struct cf_ctrset_entry*) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 

__attribute__((used)) static bool s390_cpumcfdg_testctr(struct perf_sample *sample)
{
	size_t len = sample->raw_size, offset = 0;
	unsigned char *buf = sample->raw_data;
	struct cf_trailer_entry *te;
	struct cf_ctrset_entry *cep, ce;

	if (!len)
		return false;
	while (offset < len) {
		cep = (struct cf_ctrset_entry *)(buf + offset);
		ce.def = be16_to_cpu(cep->def);
		ce.set = be16_to_cpu(cep->set);
		ce.ctr = be16_to_cpu(cep->ctr);
		ce.res1 = be16_to_cpu(cep->res1);

		if (!ctrset_valid(&ce) || offset + ctrset_size(&ce) > len) {
			/* Raw data for counter sets are always multiple of 8
			 * bytes. Prepending a 4 bytes size field to the
			 * raw data block in the sample causes the perf tool
			 * to append 4 padding bytes to make the raw data part
			 * of the sample a multiple of eight bytes again.
			 *
			 * If the last entry (trailer) is 4 bytes off the raw
			 * area data end, all is good.
			 */
			if (len - offset - sizeof(*te) == 4)
				break;
			pr_err("Invalid counter set entry at %zd\n", offset);
			return false;
		}
		offset += ctrset_size(&ce);
	}
	return true;
}