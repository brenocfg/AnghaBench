#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ classid; unsigned long class; } ;
struct route4_filter {TYPE_1__ res; } ;

/* Variables and functions */

__attribute__((used)) static void route4_bind_class(void *fh, u32 classid, unsigned long cl)
{
	struct route4_filter *f = fh;

	if (f && f->res.classid == classid)
		f->res.class = cl;
}