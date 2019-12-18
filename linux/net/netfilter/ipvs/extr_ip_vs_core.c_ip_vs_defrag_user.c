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
typedef  enum ip_defrag_users { ____Placeholder_ip_defrag_users } ip_defrag_users ;

/* Variables and functions */
 int IP_DEFRAG_VS_FWD ; 
 int IP_DEFRAG_VS_IN ; 
 int IP_DEFRAG_VS_OUT ; 
 unsigned int NF_INET_FORWARD ; 
 unsigned int NF_INET_LOCAL_IN ; 

__attribute__((used)) static inline enum ip_defrag_users ip_vs_defrag_user(unsigned int hooknum)
{
	if (NF_INET_LOCAL_IN == hooknum)
		return IP_DEFRAG_VS_IN;
	if (NF_INET_FORWARD == hooknum)
		return IP_DEFRAG_VS_FWD;
	return IP_DEFRAG_VS_OUT;
}