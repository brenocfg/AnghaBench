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
struct btf_header {int str_off; int str_len; } ;
struct btf {char* nohdr_data; char const* strings; struct btf_header* hdr; } ;
typedef  int /*<<< orphan*/  btf_print_fn_t ;

/* Variables and functions */
 int BTF_MAX_NAME_OFFSET ; 
 int EINVAL ; 
 int /*<<< orphan*/  elog (char*) ; 

__attribute__((used)) static int btf_parse_str_sec(struct btf *btf, btf_print_fn_t err_log)
{
	const struct btf_header *hdr = btf->hdr;
	const char *start = btf->nohdr_data + hdr->str_off;
	const char *end = start + btf->hdr->str_len;

	if (!hdr->str_len || hdr->str_len - 1 > BTF_MAX_NAME_OFFSET ||
	    start[0] || end[-1]) {
		elog("Invalid BTF string section\n");
		return -EINVAL;
	}

	btf->strings = start;

	return 0;
}