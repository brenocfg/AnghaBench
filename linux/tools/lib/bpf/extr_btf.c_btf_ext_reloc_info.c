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
struct btf_ext_info_sec {scalar_t__ num_info; int /*<<< orphan*/  data; int /*<<< orphan*/  sec_name_off; } ;
struct btf_ext_info {scalar_t__ rec_size; scalar_t__ len; struct btf_ext_info_sec* info; } ;
struct btf {int dummy; } ;
struct bpf_insn {int dummy; } ;
typedef  scalar_t__ __u64 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 char* btf__name_by_offset (struct btf const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* realloc (void*,scalar_t__) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int btf_ext_reloc_info(const struct btf *btf,
			      const struct btf_ext_info *ext_info,
			      const char *sec_name, __u32 insns_cnt,
			      void **info, __u32 *cnt)
{
	__u32 sec_hdrlen = sizeof(struct btf_ext_info_sec);
	__u32 i, record_size, existing_len, records_len;
	struct btf_ext_info_sec *sinfo;
	const char *info_sec_name;
	__u64 remain_len;
	void *data;

	record_size = ext_info->rec_size;
	sinfo = ext_info->info;
	remain_len = ext_info->len;
	while (remain_len > 0) {
		records_len = sinfo->num_info * record_size;
		info_sec_name = btf__name_by_offset(btf, sinfo->sec_name_off);
		if (strcmp(info_sec_name, sec_name)) {
			remain_len -= sec_hdrlen + records_len;
			sinfo = (void *)sinfo + sec_hdrlen + records_len;
			continue;
		}

		existing_len = (*cnt) * record_size;
		data = realloc(*info, existing_len + records_len);
		if (!data)
			return -ENOMEM;

		memcpy(data + existing_len, sinfo->data, records_len);
		/* adjust insn_off only, the rest data will be passed
		 * to the kernel.
		 */
		for (i = 0; i < sinfo->num_info; i++) {
			__u32 *insn_off;

			insn_off = data + existing_len + (i * record_size);
			*insn_off = *insn_off / sizeof(struct bpf_insn) +
				insns_cnt;
		}
		*info = data;
		*cnt += sinfo->num_info;
		return 0;
	}

	return -ENOENT;
}