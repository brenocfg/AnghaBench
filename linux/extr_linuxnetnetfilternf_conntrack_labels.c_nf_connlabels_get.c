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
struct TYPE_2__ {int /*<<< orphan*/  labels_used; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int BIT_WORD (unsigned int) ; 
 int ERANGE ; 
 int NF_CT_LABELS_MAX_SIZE ; 
 int /*<<< orphan*/  nf_connlabels_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int nf_connlabels_get(struct net *net, unsigned int bits)
{
	if (BIT_WORD(bits) >= NF_CT_LABELS_MAX_SIZE / sizeof(long))
		return -ERANGE;

	spin_lock(&nf_connlabels_lock);
	net->ct.labels_used++;
	spin_unlock(&nf_connlabels_lock);

	return 0;
}