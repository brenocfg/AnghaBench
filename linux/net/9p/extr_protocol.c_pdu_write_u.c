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
struct p9_fcall {size_t size; int /*<<< orphan*/ * sdata; scalar_t__ capacity; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_from_iter_full (int /*<<< orphan*/ *,size_t,struct iov_iter*) ; 
 size_t min (scalar_t__,size_t) ; 

__attribute__((used)) static size_t
pdu_write_u(struct p9_fcall *pdu, struct iov_iter *from, size_t size)
{
	size_t len = min(pdu->capacity - pdu->size, size);
	struct iov_iter i = *from;
	if (!copy_from_iter_full(&pdu->sdata[pdu->size], len, &i))
		len = 0;

	pdu->size += len;
	return size - len;
}