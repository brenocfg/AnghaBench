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
typedef  int errseq_t ;

/* Variables and functions */
 int ERRSEQ_SEEN ; 
 int MAX_ERRNO ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  cmpxchg (int*,int,int) ; 

int errseq_check_and_advance(errseq_t *eseq, errseq_t *since)
{
	int err = 0;
	errseq_t old, new;

	/*
	 * Most callers will want to use the inline wrapper to check this,
	 * so that the common case of no error is handled without needing
	 * to take the lock that protects the "since" value.
	 */
	old = READ_ONCE(*eseq);
	if (old != *since) {
		/*
		 * Set the flag and try to swap it into place if it has
		 * changed.
		 *
		 * We don't care about the outcome of the swap here. If the
		 * swap doesn't occur, then it has either been updated by a
		 * writer who is altering the value in some way (updating
		 * counter or resetting the error), or another reader who is
		 * just setting the "seen" flag. Either outcome is OK, and we
		 * can advance "since" and return an error based on what we
		 * have.
		 */
		new = old | ERRSEQ_SEEN;
		if (new != old)
			cmpxchg(eseq, old, new);
		*since = new;
		err = -(new & MAX_ERRNO);
	}
	return err;
}