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
struct nf_conn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int ctnetlink_secctx_size(const struct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTRACK_SECMARK
	int len, ret;

	ret = security_secid_to_secctx(ct->secmark, NULL, &len);
	if (ret)
		return 0;

	return nla_total_size(0) /* CTA_SECCTX */
	       + nla_total_size(sizeof(char) * len); /* CTA_SECCTX_NAME */
#else
	return 0;
#endif
}