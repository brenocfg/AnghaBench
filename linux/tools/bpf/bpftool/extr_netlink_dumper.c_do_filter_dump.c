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
struct tcmsg {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_DUMP_STR (char*,char*,char const*) ; 
 int /*<<< orphan*/  NET_DUMP_UINT (char*,char*,int) ; 
 int /*<<< orphan*/  NET_END_OBJECT_FINAL ; 
 int /*<<< orphan*/  NET_START_OBJECT ; 
 size_t TCA_KIND ; 
 size_t TCA_OPTIONS ; 
 int do_bpf_filter_dump (struct nlattr*) ; 
 int /*<<< orphan*/  libbpf_nla_data (struct nlattr*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int do_filter_dump(struct tcmsg *info, struct nlattr **tb, const char *kind,
		   const char *devname, int ifindex)
{
	int ret = 0;

	if (tb[TCA_OPTIONS] &&
	    strcmp(libbpf_nla_data(tb[TCA_KIND]), "bpf") == 0) {
		NET_START_OBJECT;
		if (devname[0] != '\0')
			NET_DUMP_STR("devname", "%s", devname);
		NET_DUMP_UINT("ifindex", "(%u)", ifindex);
		NET_DUMP_STR("kind", " %s", kind);
		ret = do_bpf_filter_dump(tb[TCA_OPTIONS]);
		NET_END_OBJECT_FINAL;
	}

	return ret;
}