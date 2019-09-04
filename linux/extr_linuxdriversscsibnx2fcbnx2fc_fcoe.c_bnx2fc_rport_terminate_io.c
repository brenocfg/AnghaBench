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
struct fc_rport {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void bnx2fc_rport_terminate_io(struct fc_rport *rport)
{
	/* This is a no-op */
}