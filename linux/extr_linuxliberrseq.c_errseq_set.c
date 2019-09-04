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
 int /*<<< orphan*/  BUILD_BUG_ON_NOT_POWER_OF_2 (int) ; 
 scalar_t__ ERRSEQ_CTR_INC ; 
 int ERRSEQ_SEEN ; 
 int MAX_ERRNO ; 
 int READ_ONCE (int) ; 
 scalar_t__ WARN (int /*<<< orphan*/ ,char*,int) ; 
 int cmpxchg (int*,int,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  unlikely (int) ; 

errseq_t errseq_set(errseq_t *eseq, int err)
{
	errseq_t cur, old;

	/* MAX_ERRNO must be able to serve as a mask */
	BUILD_BUG_ON_NOT_POWER_OF_2(MAX_ERRNO + 1);

	/*
	 * Ensure the error code actually fits where we want it to go. If it
	 * doesn't then just throw a warning and don't record anything. We
	 * also don't accept zero here as that would effectively clear a
	 * previous error.
	 */
	old = READ_ONCE(*eseq);

	if (WARN(unlikely(err == 0 || (unsigned int)-err > MAX_ERRNO),
				"err = %d\n", err))
		return old;

	for (;;) {
		errseq_t new;

		/* Clear out error bits and set new error */
		new = (old & ~(MAX_ERRNO|ERRSEQ_SEEN)) | -err;

		/* Only increment if someone has looked at it */
		if (old & ERRSEQ_SEEN)
			new += ERRSEQ_CTR_INC;

		/* If there would be no change, then call it done */
		if (new == old) {
			cur = new;
			break;
		}

		/* Try to swap the new value into place */
		cur = cmpxchg(eseq, old, new);

		/*
		 * Call it success if we did the swap or someone else beat us
		 * to it for the same value.
		 */
		if (likely(cur == old || cur == new))
			break;

		/* Raced with an update, try again */
		old = cur;
	}
	return cur;
}