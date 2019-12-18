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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t min (scalar_t__,size_t) ; 

__attribute__((used)) static size_t pdu_write(struct p9_fcall *pdu, const void *data, size_t size)
{
	size_t len = min(pdu->capacity - pdu->size, size);
	memcpy(&pdu->sdata[pdu->size], data, len);
	pdu->size += len;
	return size - len;
}