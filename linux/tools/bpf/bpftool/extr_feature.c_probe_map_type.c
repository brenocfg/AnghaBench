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
typedef  int /*<<< orphan*/  plain_desc ;
typedef  enum bpf_map_type { ____Placeholder_bpf_map_type } bpf_map_type ;
typedef  int /*<<< orphan*/  define_name ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int bpf_probe_map_type (int,int /*<<< orphan*/ ) ; 
 char** map_type_name ; 
 int /*<<< orphan*/  p_info (char*) ; 
 int /*<<< orphan*/  print_bool_feature (char*,char*,char*,int,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  uppercase (char*,int) ; 

__attribute__((used)) static void
probe_map_type(enum bpf_map_type map_type, const char *define_prefix,
	       __u32 ifindex)
{
	char feat_name[128], plain_desc[128], define_name[128];
	const char *plain_comment = "eBPF map_type ";
	size_t maxlen;
	bool res;

	res = bpf_probe_map_type(map_type, ifindex);

	maxlen = sizeof(plain_desc) - strlen(plain_comment) - 1;
	if (strlen(map_type_name[map_type]) > maxlen) {
		p_info("map type name too long");
		return;
	}

	sprintf(feat_name, "have_%s_map_type", map_type_name[map_type]);
	sprintf(define_name, "%s_map_type", map_type_name[map_type]);
	uppercase(define_name, sizeof(define_name));
	sprintf(plain_desc, "%s%s", plain_comment, map_type_name[map_type]);
	print_bool_feature(feat_name, plain_desc, define_name, res,
			   define_prefix);
}