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
struct ovs_key_ct_labels {int dummy; } ;
struct nf_conn_labels {int /*<<< orphan*/  bits; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVS_CT_LABELS_LEN ; 
 int /*<<< orphan*/  memcpy (struct ovs_key_ct_labels*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ovs_key_ct_labels*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conn_labels* nf_ct_labels_find (struct nf_conn const*) ; 

__attribute__((used)) static void ovs_ct_get_labels(const struct nf_conn *ct,
			      struct ovs_key_ct_labels *labels)
{
	struct nf_conn_labels *cl = ct ? nf_ct_labels_find(ct) : NULL;

	if (cl)
		memcpy(labels, cl->bits, OVS_CT_LABELS_LEN);
	else
		memset(labels, 0, OVS_CT_LABELS_LEN);
}