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
struct nf_ct_bridge_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (struct nf_ct_bridge_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nf_ct_bridge_info* nf_ct_bridge_info ; 
 int /*<<< orphan*/  nf_ct_proto_mutex ; 

void nf_ct_bridge_register(struct nf_ct_bridge_info *info)
{
	WARN_ON(nf_ct_bridge_info);
	mutex_lock(&nf_ct_proto_mutex);
	nf_ct_bridge_info = info;
	mutex_unlock(&nf_ct_proto_mutex);
}