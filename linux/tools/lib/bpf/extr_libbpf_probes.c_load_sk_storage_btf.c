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
typedef  int /*<<< orphan*/  types ;
typedef  int /*<<< orphan*/  strs ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_INFO_ENC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BTF_INT_SIGNED ; 
 int /*<<< orphan*/  BTF_KIND_STRUCT ; 
 int /*<<< orphan*/  BTF_MEMBER_ENC (int,int,int) ; 
 int /*<<< orphan*/  BTF_TYPE_ENC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BTF_TYPE_INT_ENC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int libbpf__load_raw_btf (char*,int,char const*,int) ; 

__attribute__((used)) static int load_sk_storage_btf(void)
{
	const char strs[] = "\0bpf_spin_lock\0val\0cnt\0l";
	/* struct bpf_spin_lock {
	 *   int val;
	 * };
	 * struct val {
	 *   int cnt;
	 *   struct bpf_spin_lock l;
	 * };
	 */
	__u32 types[] = {
		/* int */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* struct bpf_spin_lock */                      /* [2] */
		BTF_TYPE_ENC(1, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 4),
		BTF_MEMBER_ENC(15, 1, 0), /* int val; */
		/* struct val */                                /* [3] */
		BTF_TYPE_ENC(15, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 8),
		BTF_MEMBER_ENC(19, 1, 0), /* int cnt; */
		BTF_MEMBER_ENC(23, 2, 32),/* struct bpf_spin_lock l; */
	};

	return libbpf__load_raw_btf((char *)types, sizeof(types),
				     strs, sizeof(strs));
}