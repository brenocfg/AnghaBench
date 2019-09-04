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
struct urb {int dummy; } ;
struct oxu_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  oxu_dbg (struct oxu_hcd*,char*) ; 

__attribute__((used)) static inline int itd_submit(struct oxu_hcd *oxu, struct urb *urb,
						gfp_t mem_flags)
{
	oxu_dbg(oxu, "iso support is missing!\n");
	return -ENOSYS;
}