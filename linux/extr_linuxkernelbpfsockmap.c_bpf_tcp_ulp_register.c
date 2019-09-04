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
 size_t SOCKMAP_IPV4 ; 
 int /*<<< orphan*/ * bpf_tcp_prots ; 
 int /*<<< orphan*/  bpf_tcp_ulp_ops ; 
 int /*<<< orphan*/  build_protos (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_prot ; 
 int tcp_register_ulp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpf_tcp_ulp_register(void)
{
	build_protos(bpf_tcp_prots[SOCKMAP_IPV4], &tcp_prot);
	/* Once BPF TX ULP is registered it is never unregistered. It
	 * will be in the ULP list for the lifetime of the system. Doing
	 * duplicate registers is not a problem.
	 */
	return tcp_register_ulp(&bpf_tcp_ulp_ops);
}