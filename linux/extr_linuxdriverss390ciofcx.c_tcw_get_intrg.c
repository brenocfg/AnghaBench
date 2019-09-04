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
struct tcw {scalar_t__ intrg; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */

struct tcw *tcw_get_intrg(struct tcw *tcw)
{
	return (struct tcw *) ((addr_t) tcw->intrg);
}