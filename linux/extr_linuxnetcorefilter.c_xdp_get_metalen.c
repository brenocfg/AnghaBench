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
struct xdp_buff {unsigned long data; unsigned long data_meta; } ;

/* Variables and functions */
 scalar_t__ xdp_data_meta_unsupported (struct xdp_buff const*) ; 

__attribute__((used)) static unsigned long xdp_get_metalen(const struct xdp_buff *xdp)
{
	return xdp_data_meta_unsupported(xdp) ? 0 :
	       xdp->data - xdp->data_meta;
}