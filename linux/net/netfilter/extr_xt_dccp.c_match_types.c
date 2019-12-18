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
typedef  int u_int16_t ;
struct dccp_hdr {int dccph_type; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
match_types(const struct dccp_hdr *dh, u_int16_t typemask)
{
	return typemask & (1 << dh->dccph_type);
}