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
struct fcloop_fcpreq {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  fcloop_tfcp_req_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fcloop_tfcp_req_put(struct fcloop_fcpreq *tfcp_req)
{
	kref_put(&tfcp_req->ref, fcloop_tfcp_req_free);
}