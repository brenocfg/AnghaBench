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
struct cxgbit_sock {int lock_owner; int /*<<< orphan*/  lock; scalar_t__ snd_win; scalar_t__ snd_una; int /*<<< orphan*/  write_seq; } ;

/* Variables and functions */
 scalar_t__ before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cxgbit_lock_sock(struct cxgbit_sock *csk)
{
	spin_lock_bh(&csk->lock);

	if (before(csk->write_seq, csk->snd_una + csk->snd_win))
		csk->lock_owner = true;

	spin_unlock_bh(&csk->lock);

	return csk->lock_owner;
}