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
struct TYPE_2__ {int /*<<< orphan*/  labels; } ;
struct sw_flow_key {TYPE_1__ ct; } ;
struct ovs_key_ct_labels {int /*<<< orphan*/  ct_labels_32; } ;
struct nf_conn_labels {int /*<<< orphan*/  bits; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  OVS_CT_LABELS_LEN ; 
 int /*<<< orphan*/  OVS_CT_LABELS_LEN_32 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nf_connlabels_replace (struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conn_labels* ovs_ct_get_conn_labels (struct nf_conn*) ; 

__attribute__((used)) static int ovs_ct_set_labels(struct nf_conn *ct, struct sw_flow_key *key,
			     const struct ovs_key_ct_labels *labels,
			     const struct ovs_key_ct_labels *mask)
{
	struct nf_conn_labels *cl;
	int err;

	cl = ovs_ct_get_conn_labels(ct);
	if (!cl)
		return -ENOSPC;

	err = nf_connlabels_replace(ct, labels->ct_labels_32,
				    mask->ct_labels_32,
				    OVS_CT_LABELS_LEN_32);
	if (err)
		return err;

	memcpy(&key->ct.labels, cl->bits, OVS_CT_LABELS_LEN);

	return 0;
}