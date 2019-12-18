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
typedef  int /*<<< orphan*/  ulong ;
typedef  scalar_t__ u8 ;
struct bnep_session {long long mc_filter; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__* broadcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNEP_FILTER_MULTI_ADDR_RSP ; 
 int /*<<< orphan*/  BNEP_FILTER_UNSUPPORTED_REQ ; 
 int /*<<< orphan*/  BNEP_SUCCESS ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int EILSEQ ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  bnep_mc_hash (scalar_t__*) ; 
 int /*<<< orphan*/  bnep_send_rsp (struct bnep_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_unaligned_be16 (scalar_t__*) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnep_ctrl_set_mcfilter(struct bnep_session *s, u8 *data, int len)
{
	int n;

	if (len < 2)
		return -EILSEQ;

	n = get_unaligned_be16(data);
	data += 2;
	len -= 2;

	if (len < n)
		return -EILSEQ;

	BT_DBG("filter len %d", n);

#ifdef CONFIG_BT_BNEP_MC_FILTER
	n /= (ETH_ALEN * 2);

	if (n > 0) {
		int i;

		s->mc_filter = 0;

		/* Always send broadcast */
		set_bit(bnep_mc_hash(s->dev->broadcast), (ulong *) &s->mc_filter);

		/* Add address ranges to the multicast hash */
		for (; n > 0; n--) {
			u8 a1[6], *a2;

			memcpy(a1, data, ETH_ALEN);
			data += ETH_ALEN;
			a2 = data;
			data += ETH_ALEN;

			BT_DBG("mc filter %pMR -> %pMR", a1, a2);

			/* Iterate from a1 to a2 */
			set_bit(bnep_mc_hash(a1), (ulong *) &s->mc_filter);
			while (memcmp(a1, a2, 6) < 0 && s->mc_filter != ~0LL) {
				/* Increment a1 */
				i = 5;
				while (i >= 0 && ++a1[i--] == 0)
					;

				set_bit(bnep_mc_hash(a1), (ulong *) &s->mc_filter);
			}
		}
	}

	BT_DBG("mc filter hash 0x%llx", s->mc_filter);

	bnep_send_rsp(s, BNEP_FILTER_MULTI_ADDR_RSP, BNEP_SUCCESS);
#else
	bnep_send_rsp(s, BNEP_FILTER_MULTI_ADDR_RSP, BNEP_FILTER_UNSUPPORTED_REQ);
#endif
	return 0;
}