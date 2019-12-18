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

/* Variables and functions */
 int /*<<< orphan*/  LWTUNNEL_ENCAP_ILA ; 
 int /*<<< orphan*/  ila_encap_ops ; 
 int /*<<< orphan*/  lwtunnel_encap_del_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ila_lwt_fini(void)
{
	lwtunnel_encap_del_ops(&ila_encap_ops, LWTUNNEL_ENCAP_ILA);
}