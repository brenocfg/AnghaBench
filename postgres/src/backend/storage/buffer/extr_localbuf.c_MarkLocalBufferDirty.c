#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  local_blks_dirtied; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ BufferDesc ;
typedef  int Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_DIRTY ; 
 int BufferIsLocal (int) ; 
 TYPE_1__* GetLocalBufferDescriptor (int) ; 
 scalar_t__* LocalRefCount ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ pgBufferUsage ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_atomic_unlocked_write_u32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

void
MarkLocalBufferDirty(Buffer buffer)
{
	int			bufid;
	BufferDesc *bufHdr;
	uint32		buf_state;

	Assert(BufferIsLocal(buffer));

#ifdef LBDEBUG
	fprintf(stderr, "LB DIRTY %d\n", buffer);
#endif

	bufid = -(buffer + 1);

	Assert(LocalRefCount[bufid] > 0);

	bufHdr = GetLocalBufferDescriptor(bufid);

	buf_state = pg_atomic_read_u32(&bufHdr->state);

	if (!(buf_state & BM_DIRTY))
		pgBufferUsage.local_blks_dirtied++;

	buf_state |= BM_DIRTY;

	pg_atomic_unlocked_write_u32(&bufHdr->state, buf_state);
}