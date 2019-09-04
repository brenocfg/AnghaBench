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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  labels; } ;
struct sw_flow_key {TYPE_1__ ct; } ;
struct ovs_key_ct_labels {int* ct_labels_32; } ;
struct nf_conn_labels {scalar_t__ bits; } ;
struct nf_conn {scalar_t__ master; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IPCT_LABEL ; 
 int /*<<< orphan*/  OVS_CT_LABELS_LEN ; 
 int OVS_CT_LABELS_LEN_32 ; 
 int labels_nonzero (struct ovs_key_ct_labels const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 struct nf_conn_labels* nf_ct_labels_find (scalar_t__) ; 
 struct nf_conn_labels* ovs_ct_get_conn_labels (struct nf_conn*) ; 

__attribute__((used)) static int ovs_ct_init_labels(struct nf_conn *ct, struct sw_flow_key *key,
			      const struct ovs_key_ct_labels *labels,
			      const struct ovs_key_ct_labels *mask)
{
	struct nf_conn_labels *cl, *master_cl;
	bool have_mask = labels_nonzero(mask);

	/* Inherit master's labels to the related connection? */
	master_cl = ct->master ? nf_ct_labels_find(ct->master) : NULL;

	if (!master_cl && !have_mask)
		return 0;   /* Nothing to do. */

	cl = ovs_ct_get_conn_labels(ct);
	if (!cl)
		return -ENOSPC;

	/* Inherit the master's labels, if any. */
	if (master_cl)
		*cl = *master_cl;

	if (have_mask) {
		u32 *dst = (u32 *)cl->bits;
		int i;

		for (i = 0; i < OVS_CT_LABELS_LEN_32; i++)
			dst[i] = (dst[i] & ~mask->ct_labels_32[i]) |
				(labels->ct_labels_32[i]
				 & mask->ct_labels_32[i]);
	}

	/* Labels are included in the IPCTNL_MSG_CT_NEW event only if the
	 * IPCT_LABEL bit is set in the event cache.
	 */
	nf_conntrack_event_cache(IPCT_LABEL, ct);

	memcpy(&key->ct.labels, cl->bits, OVS_CT_LABELS_LEN);

	return 0;
}