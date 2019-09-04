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
struct TYPE_2__ {int /*<<< orphan*/  (* unlock ) (struct strparser*) ;int /*<<< orphan*/  (* lock ) (struct strparser*) ;} ;
struct strparser {TYPE_1__ cb; int /*<<< orphan*/  work; scalar_t__ paused; int /*<<< orphan*/  stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strp_read_sock (struct strparser*) ; 
 int /*<<< orphan*/  strp_wq ; 
 int /*<<< orphan*/  stub1 (struct strparser*) ; 
 int /*<<< orphan*/  stub2 (struct strparser*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_strp_work(struct strparser *strp)
{
	/* We need the read lock to synchronize with strp_data_ready. We
	 * need the socket lock for calling strp_read_sock.
	 */
	strp->cb.lock(strp);

	if (unlikely(strp->stopped))
		goto out;

	if (strp->paused)
		goto out;

	if (strp_read_sock(strp) == -ENOMEM)
		queue_work(strp_wq, &strp->work);

out:
	strp->cb.unlock(strp);
}