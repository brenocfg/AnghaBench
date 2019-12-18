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
typedef  int u64 ;

/* Variables and functions */
 unsigned short AF_INET ; 
 unsigned short AF_INET6 ; 
 int BPF_F_TUNINFO_IPV6 ; 

__attribute__((used)) static unsigned short bpf_tunnel_key_af(u64 flags)
{
	return flags & BPF_F_TUNINFO_IPV6 ? AF_INET6 : AF_INET;
}