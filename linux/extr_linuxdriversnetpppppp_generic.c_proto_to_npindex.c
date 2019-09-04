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
 int EINVAL ; 
 int NP_AT ; 
 int NP_IP ; 
 int NP_IPV6 ; 
 int NP_IPX ; 
 int NP_MPLS_MC ; 
 int NP_MPLS_UC ; 
#define  PPP_AT 133 
#define  PPP_IP 132 
#define  PPP_IPV6 131 
#define  PPP_IPX 130 
#define  PPP_MPLS_MC 129 
#define  PPP_MPLS_UC 128 

__attribute__((used)) static inline int proto_to_npindex(int proto)
{
	switch (proto) {
	case PPP_IP:
		return NP_IP;
	case PPP_IPV6:
		return NP_IPV6;
	case PPP_IPX:
		return NP_IPX;
	case PPP_AT:
		return NP_AT;
	case PPP_MPLS_UC:
		return NP_MPLS_UC;
	case PPP_MPLS_MC:
		return NP_MPLS_MC;
	}
	return -EINVAL;
}