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
struct amt_host_if {int initialized; int /*<<< orphan*/  mei_cl; } ;

/* Variables and functions */
 int /*<<< orphan*/  mei_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amt_host_if_deinit(struct amt_host_if *acmd)
{
	mei_deinit(&acmd->mei_cl);
	acmd->initialized = false;
}