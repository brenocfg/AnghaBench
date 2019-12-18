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
struct ndmsg {int dummy; } ;

/* Variables and functions */
 int MAX_ADDR_LEN ; 
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static inline size_t pneigh_nlmsg_size(void)
{
	return NLMSG_ALIGN(sizeof(struct ndmsg))
	       + nla_total_size(MAX_ADDR_LEN) /* NDA_DST */
	       + nla_total_size(1); /* NDA_PROTOCOL */
}