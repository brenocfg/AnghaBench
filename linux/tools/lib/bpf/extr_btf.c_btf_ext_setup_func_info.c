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
struct btf_ext {int /*<<< orphan*/  func_info; TYPE_1__* hdr; } ;
struct bpf_func_info_min {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  func_info_len; int /*<<< orphan*/  func_info_off; } ;

/* Variables and functions */
 int btf_ext_setup_info (struct btf_ext*,struct btf_ext_sec_setup_param*) ; 

__attribute__((used)) static int btf_ext_setup_func_info(struct btf_ext *btf_ext)
{
	struct btf_ext_sec_setup_param param = {
		.off = btf_ext->hdr->func_info_off,
		.len = btf_ext->hdr->func_info_len,
		.min_rec_size = sizeof(struct bpf_func_info_min),
		.ext_info = &btf_ext->func_info,
		.desc = "func_info"
	};

	return btf_ext_setup_info(btf_ext, &param);
}