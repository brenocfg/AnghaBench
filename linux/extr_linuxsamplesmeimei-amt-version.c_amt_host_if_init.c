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
struct amt_host_if {unsigned long send_timeout; int initialized; int /*<<< orphan*/  mei_cl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_IAMTHIF ; 
 int mei_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool amt_host_if_init(struct amt_host_if *acmd,
		      unsigned long send_timeout, bool verbose)
{
	acmd->send_timeout = (send_timeout) ? send_timeout : 20000;
	acmd->initialized = mei_init(&acmd->mei_cl, &MEI_IAMTHIF, 0, verbose);
	return acmd->initialized;
}