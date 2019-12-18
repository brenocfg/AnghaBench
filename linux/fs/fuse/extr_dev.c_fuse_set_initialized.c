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
struct fuse_conn {int initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 

void fuse_set_initialized(struct fuse_conn *fc)
{
	/* Make sure stores before this are seen on another CPU */
	smp_wmb();
	fc->initialized = 1;
}