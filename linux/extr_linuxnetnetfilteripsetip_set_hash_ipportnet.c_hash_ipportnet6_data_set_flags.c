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
typedef  int u32 ;
struct hash_ipportnet6_elem {int nomatch; } ;

/* Variables and functions */
 int IPSET_FLAG_NOMATCH ; 

__attribute__((used)) static inline void
hash_ipportnet6_data_set_flags(struct hash_ipportnet6_elem *elem, u32 flags)
{
	elem->nomatch = !!((flags >> 16) & IPSET_FLAG_NOMATCH);
}