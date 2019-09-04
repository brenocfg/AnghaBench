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
struct fib6_info {scalar_t__ dst_host; scalar_t__ dst_nopolicy; scalar_t__ dst_nocount; } ;

/* Variables and functions */
 unsigned short DST_HOST ; 
 unsigned short DST_NOCOUNT ; 
 unsigned short DST_NOPOLICY ; 

__attribute__((used)) static unsigned short fib6_info_dst_flags(struct fib6_info *rt)
{
	unsigned short flags = 0;

	if (rt->dst_nocount)
		flags |= DST_NOCOUNT;
	if (rt->dst_nopolicy)
		flags |= DST_NOPOLICY;
	if (rt->dst_host)
		flags |= DST_HOST;

	return flags;
}