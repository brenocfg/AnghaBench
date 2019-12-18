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
struct btf_header {scalar_t__ magic; scalar_t__ version; int type_off; int str_off; scalar_t__ flags; } ;
struct btf {int data_size; struct btf_header* hdr; struct btf_header* nohdr_data; } ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ BTF_MAGIC ; 
 scalar_t__ BTF_VERSION ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int btf_parse_hdr(struct btf *btf)
{
	const struct btf_header *hdr = btf->hdr;
	__u32 meta_left;

	if (btf->data_size < sizeof(struct btf_header)) {
		pr_debug("BTF header not found\n");
		return -EINVAL;
	}

	if (hdr->magic != BTF_MAGIC) {
		pr_debug("Invalid BTF magic:%x\n", hdr->magic);
		return -EINVAL;
	}

	if (hdr->version != BTF_VERSION) {
		pr_debug("Unsupported BTF version:%u\n", hdr->version);
		return -ENOTSUP;
	}

	if (hdr->flags) {
		pr_debug("Unsupported BTF flags:%x\n", hdr->flags);
		return -ENOTSUP;
	}

	meta_left = btf->data_size - sizeof(*hdr);
	if (!meta_left) {
		pr_debug("BTF has no data\n");
		return -EINVAL;
	}

	if (meta_left < hdr->type_off) {
		pr_debug("Invalid BTF type section offset:%u\n", hdr->type_off);
		return -EINVAL;
	}

	if (meta_left < hdr->str_off) {
		pr_debug("Invalid BTF string section offset:%u\n", hdr->str_off);
		return -EINVAL;
	}

	if (hdr->type_off >= hdr->str_off) {
		pr_debug("BTF type section offset >= string section offset. No type?\n");
		return -EINVAL;
	}

	if (hdr->type_off & 0x02) {
		pr_debug("BTF type section is not aligned to 4 bytes\n");
		return -EINVAL;
	}

	btf->nohdr_data = btf->hdr + 1;

	return 0;
}