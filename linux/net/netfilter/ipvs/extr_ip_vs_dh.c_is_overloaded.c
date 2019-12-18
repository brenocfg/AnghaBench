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
struct ip_vs_dest {int flags; } ;

/* Variables and functions */
 int IP_VS_DEST_F_OVERLOAD ; 

__attribute__((used)) static inline int is_overloaded(struct ip_vs_dest *dest)
{
	return dest->flags & IP_VS_DEST_F_OVERLOAD;
}