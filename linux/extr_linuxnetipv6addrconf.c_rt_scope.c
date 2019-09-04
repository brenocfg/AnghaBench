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
 int IFA_HOST ; 
 int IFA_LINK ; 
 int IFA_SITE ; 
 int RT_SCOPE_HOST ; 
 int RT_SCOPE_LINK ; 
 int RT_SCOPE_SITE ; 
 int RT_SCOPE_UNIVERSE ; 

__attribute__((used)) static inline int rt_scope(int ifa_scope)
{
	if (ifa_scope & IFA_HOST)
		return RT_SCOPE_HOST;
	else if (ifa_scope & IFA_LINK)
		return RT_SCOPE_LINK;
	else if (ifa_scope & IFA_SITE)
		return RT_SCOPE_SITE;
	else
		return RT_SCOPE_UNIVERSE;
}