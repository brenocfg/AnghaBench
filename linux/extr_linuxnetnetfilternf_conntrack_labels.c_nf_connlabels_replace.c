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
typedef  int /*<<< orphan*/  u32 ;
struct nf_conn_labels {scalar_t__ bits; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IPCT_LABEL ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 struct nf_conn_labels* nf_ct_labels_find (struct nf_conn*) ; 
 int replace_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

int nf_connlabels_replace(struct nf_conn *ct,
			  const u32 *data,
			  const u32 *mask, unsigned int words32)
{
	struct nf_conn_labels *labels;
	unsigned int size, i;
	int changed = 0;
	u32 *dst;

	labels = nf_ct_labels_find(ct);
	if (!labels)
		return -ENOSPC;

	size = sizeof(labels->bits);
	if (size < (words32 * sizeof(u32)))
		words32 = size / sizeof(u32);

	dst = (u32 *) labels->bits;
	for (i = 0; i < words32; i++)
		changed |= replace_u32(&dst[i], mask ? ~mask[i] : 0, data[i]);

	size /= sizeof(u32);
	for (i = words32; i < size; i++) /* pad */
		replace_u32(&dst[i], 0, 0);

	if (changed)
		nf_conntrack_event_cache(IPCT_LABEL, ct);
	return 0;
}