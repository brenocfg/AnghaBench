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
struct nfsd4_callback {int /*<<< orphan*/  cb_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  callback_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfsd4_run_cb(struct nfsd4_callback *cb)
{
	queue_work(callback_wq, &cb->cb_work);
}