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
struct nlm_rqst {int /*<<< orphan*/  a_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  nlmsvc_release_block (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nlmsvc_grant_release(void *data)
{
	struct nlm_rqst		*call = data;
	nlmsvc_release_block(call->a_block);
}