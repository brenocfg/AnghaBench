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
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int NLM_HOST_NRHASH ; 
 unsigned int __nlm_hash_addr4 (struct sockaddr const*) ; 
 unsigned int __nlm_hash_addr6 (struct sockaddr const*) ; 

__attribute__((used)) static unsigned int nlm_hash_address(const struct sockaddr *sap)
{
	unsigned int hash;

	switch (sap->sa_family) {
	case AF_INET:
		hash = __nlm_hash_addr4(sap);
		break;
	case AF_INET6:
		hash = __nlm_hash_addr6(sap);
		break;
	default:
		hash = 0;
	}
	return hash & (NLM_HOST_NRHASH - 1);
}