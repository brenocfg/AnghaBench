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
typedef  int u8 ;
struct sock {int dummy; } ;
struct TYPE_2__ {int dccps_pcrlen; int dccps_pcslen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCPF_MIN_CSUM_COVER ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dccp_feat_register_sp (struct sock*,int /*<<< orphan*/ ,int,int*,int) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_setsockopt_cscov(struct sock *sk, int cscov, bool rx)
{
	u8 *list, len;
	int i, rc;

	if (cscov < 0 || cscov > 15)
		return -EINVAL;
	/*
	 * Populate a list of permissible values, in the range cscov...15. This
	 * is necessary since feature negotiation of single values only works if
	 * both sides incidentally choose the same value. Since the list starts
	 * lowest-value first, negotiation will pick the smallest shared value.
	 */
	if (cscov == 0)
		return 0;
	len = 16 - cscov;

	list = kmalloc(len, GFP_KERNEL);
	if (list == NULL)
		return -ENOBUFS;

	for (i = 0; i < len; i++)
		list[i] = cscov++;

	rc = dccp_feat_register_sp(sk, DCCPF_MIN_CSUM_COVER, rx, list, len);

	if (rc == 0) {
		if (rx)
			dccp_sk(sk)->dccps_pcrlen = cscov;
		else
			dccp_sk(sk)->dccps_pcslen = cscov;
	}
	kfree(list);
	return rc;
}