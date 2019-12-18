#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__* STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  SCARD_LOCK_TCP ; 
 int STREAM_COUNT ; 
 TYPE_1__* g_out ; 
 int /*<<< orphan*/  scard_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scard_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ xrealloc (int /*<<< orphan*/ *,scalar_t__) ; 

STREAM
tcp_init(uint32 maxlen)
{
	static int cur_stream_id = 0;
	STREAM result = NULL;

#ifdef WITH_SCARD
	scard_lock(SCARD_LOCK_TCP);
#endif
	result = &g_out[cur_stream_id];
	cur_stream_id = (cur_stream_id + 1) % STREAM_COUNT;

	if (maxlen > result->size)
	{
		result->data = (uint8 *) xrealloc(result->data, maxlen);
		result->size = maxlen;
	}

	result->p = result->data;
	result->end = result->data + result->size;
#ifdef WITH_SCARD
	scard_unlock(SCARD_LOCK_TCP);
#endif
	return result;
}