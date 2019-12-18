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
typedef  size_t __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_XFRM ; 
 size_t F_FLOW_SEQ ; 
 size_t IPSEC_SHIFT ; 
 size_t IPV6_SHIFT ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 size_t NR_PKT_FLAGS ; 
 char** pkt_flag_names ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static __u32 pktgen_read_flag(const char *f, bool *disable)
{
	__u32 i;

	if (f[0] == '!') {
		*disable = true;
		f++;
	}

	for (i = 0; i < NR_PKT_FLAGS; i++) {
		if (!IS_ENABLED(CONFIG_XFRM) && i == IPSEC_SHIFT)
			continue;

		/* allow only disabling ipv6 flag */
		if (!*disable && i == IPV6_SHIFT)
			continue;

		if (strcmp(f, pkt_flag_names[i]) == 0)
			return 1 << i;
	}

	if (strcmp(f, "FLOW_RND") == 0) {
		*disable = !*disable;
		return F_FLOW_SEQ;
	}

	return 0;
}