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
struct btf_ext_sec_setup_param {int min_rec_size; char* desc; int /*<<< orphan*/ * ext_info; int /*<<< orphan*/  len; int /*<<< orphan*/  off; } ;
struct btf_ext {int /*<<< orphan*/  offset_reloc_info; TYPE_1__* hdr; } ;
struct bpf_offset_reloc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset_reloc_len; int /*<<< orphan*/  offset_reloc_off; } ;

/* Variables and functions */
 int btf_ext_setup_info (struct btf_ext*,struct btf_ext_sec_setup_param*) ; 

__attribute__((used)) static int btf_ext_setup_offset_reloc(struct btf_ext *btf_ext)
{
	struct btf_ext_sec_setup_param param = {
		.off = btf_ext->hdr->offset_reloc_off,
		.len = btf_ext->hdr->offset_reloc_len,
		.min_rec_size = sizeof(struct bpf_offset_reloc),
		.ext_info = &btf_ext->offset_reloc_info,
		.desc = "offset_reloc",
	};

	return btf_ext_setup_info(btf_ext, &param);
}