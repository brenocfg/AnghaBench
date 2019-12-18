#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct btf_ext_sec_setup_param {scalar_t__ len; int off; int min_rec_size; struct btf_ext_info* ext_info; int /*<<< orphan*/  desc; } ;
struct btf_ext_info_sec {int num_info; } ;
struct btf_ext_info {int len; int rec_size; void* info; } ;
struct btf_ext {void* data; int data_size; TYPE_1__* hdr; } ;
typedef  int __u64 ;
typedef  int __u32 ;
struct TYPE_2__ {int hdr_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int btf_ext_setup_info(struct btf_ext *btf_ext,
			      struct btf_ext_sec_setup_param *ext_sec)
{
	const struct btf_ext_info_sec *sinfo;
	struct btf_ext_info *ext_info;
	__u32 info_left, record_size;
	/* The start of the info sec (including the __u32 record_size). */
	void *info;

	if (ext_sec->len == 0)
		return 0;

	if (ext_sec->off & 0x03) {
		pr_debug(".BTF.ext %s section is not aligned to 4 bytes\n",
		     ext_sec->desc);
		return -EINVAL;
	}

	info = btf_ext->data + btf_ext->hdr->hdr_len + ext_sec->off;
	info_left = ext_sec->len;

	if (btf_ext->data + btf_ext->data_size < info + ext_sec->len) {
		pr_debug("%s section (off:%u len:%u) is beyond the end of the ELF section .BTF.ext\n",
			 ext_sec->desc, ext_sec->off, ext_sec->len);
		return -EINVAL;
	}

	/* At least a record size */
	if (info_left < sizeof(__u32)) {
		pr_debug(".BTF.ext %s record size not found\n", ext_sec->desc);
		return -EINVAL;
	}

	/* The record size needs to meet the minimum standard */
	record_size = *(__u32 *)info;
	if (record_size < ext_sec->min_rec_size ||
	    record_size & 0x03) {
		pr_debug("%s section in .BTF.ext has invalid record size %u\n",
			 ext_sec->desc, record_size);
		return -EINVAL;
	}

	sinfo = info + sizeof(__u32);
	info_left -= sizeof(__u32);

	/* If no records, return failure now so .BTF.ext won't be used. */
	if (!info_left) {
		pr_debug("%s section in .BTF.ext has no records", ext_sec->desc);
		return -EINVAL;
	}

	while (info_left) {
		unsigned int sec_hdrlen = sizeof(struct btf_ext_info_sec);
		__u64 total_record_size;
		__u32 num_records;

		if (info_left < sec_hdrlen) {
			pr_debug("%s section header is not found in .BTF.ext\n",
			     ext_sec->desc);
			return -EINVAL;
		}

		num_records = sinfo->num_info;
		if (num_records == 0) {
			pr_debug("%s section has incorrect num_records in .BTF.ext\n",
			     ext_sec->desc);
			return -EINVAL;
		}

		total_record_size = sec_hdrlen +
				    (__u64)num_records * record_size;
		if (info_left < total_record_size) {
			pr_debug("%s section has incorrect num_records in .BTF.ext\n",
			     ext_sec->desc);
			return -EINVAL;
		}

		info_left -= total_record_size;
		sinfo = (void *)sinfo + total_record_size;
	}

	ext_info = ext_sec->ext_info;
	ext_info->len = ext_sec->len - sizeof(__u32);
	ext_info->rec_size = record_size;
	ext_info->info = info + sizeof(__u32);

	return 0;
}