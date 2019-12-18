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
typedef  int /*<<< orphan*/  types ;
struct TYPE_2__ {int btf_func; } ;
struct bpf_object {TYPE_1__ caps; } ;
typedef  int /*<<< orphan*/  strs ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_INFO_ENC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BTF_INT_SIGNED ; 
 int /*<<< orphan*/  BTF_KIND_FUNC ; 
 int /*<<< orphan*/  BTF_KIND_FUNC_PROTO ; 
 int /*<<< orphan*/  BTF_PARAM_ENC (int,int) ; 
 int /*<<< orphan*/  BTF_TYPE_ENC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BTF_TYPE_INT_ENC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int libbpf__load_raw_btf (char*,int,char const*,int) ; 

__attribute__((used)) static int bpf_object__probe_btf_func(struct bpf_object *obj)
{
	const char strs[] = "\0int\0x\0a";
	/* void x(int a) {} */
	__u32 types[] = {
		/* int */
		BTF_TYPE_INT_ENC(1, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* FUNC_PROTO */                                /* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_FUNC_PROTO, 0, 1), 0),
		BTF_PARAM_ENC(7, 1),
		/* FUNC x */                                    /* [3] */
		BTF_TYPE_ENC(5, BTF_INFO_ENC(BTF_KIND_FUNC, 0, 0), 2),
	};
	int btf_fd;

	btf_fd = libbpf__load_raw_btf((char *)types, sizeof(types),
				      strs, sizeof(strs));
	if (btf_fd >= 0) {
		obj->caps.btf_func = 1;
		close(btf_fd);
		return 1;
	}

	return 0;
}