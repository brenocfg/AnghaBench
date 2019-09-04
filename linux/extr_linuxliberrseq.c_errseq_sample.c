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
 int READ_ONCE (int) ; 

errseq_t errseq_sample(errseq_t *eseq)
{
	errseq_t old = READ_ONCE(*eseq);

	/* If nobody has seen this error yet, then we can be the first. */
	if (!(old & ERRSEQ_SEEN))
		old = 0;
	return old;
}