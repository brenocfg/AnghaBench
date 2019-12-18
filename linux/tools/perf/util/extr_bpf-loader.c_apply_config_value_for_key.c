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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int BPF_LOADER_ERRNO__OBJCONF_MAP_VALUESIZE ; 
 int bpf_map_update_elem (int,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int
apply_config_value_for_key(int map_fd, void *pkey,
			   size_t val_size, u64 val)
{
	int err = 0;

	switch (val_size) {
	case 1: {
		u8 _val = (u8)(val);
		err = bpf_map_update_elem(map_fd, pkey, &_val, BPF_ANY);
		break;
	}
	case 2: {
		u16 _val = (u16)(val);
		err = bpf_map_update_elem(map_fd, pkey, &_val, BPF_ANY);
		break;
	}
	case 4: {
		u32 _val = (u32)(val);
		err = bpf_map_update_elem(map_fd, pkey, &_val, BPF_ANY);
		break;
	}
	case 8: {
		err = bpf_map_update_elem(map_fd, pkey, &val, BPF_ANY);
		break;
	}
	default:
		pr_debug("ERROR: invalid value size\n");
		return -BPF_LOADER_ERRNO__OBJCONF_MAP_VALUESIZE;
	}
	if (err && errno)
		err = -errno;
	return err;
}