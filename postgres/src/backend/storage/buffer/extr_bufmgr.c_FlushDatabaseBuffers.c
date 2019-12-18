#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_12__ {scalar_t__ dbNode; } ;
struct TYPE_11__ {TYPE_2__ rnode; } ;
struct TYPE_13__ {TYPE_1__ tag; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__ BufferDesc ;

/* Variables and functions */
 int BM_DIRTY ; 
 int BM_VALID ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (TYPE_3__*) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  FlushBuffer (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* GetBufferDescriptor (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int LockBufHdr (TYPE_3__*) ; 
 int NBuffers ; 
 int /*<<< orphan*/  PinBuffer_Locked (TYPE_3__*) ; 
 int /*<<< orphan*/  ReservePrivateRefCountEntry () ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_3__*,int) ; 
 int /*<<< orphan*/  UnpinBuffer (TYPE_3__*,int) ; 

void
FlushDatabaseBuffers(Oid dbid)
{
	int			i;
	BufferDesc *bufHdr;

	/* Make sure we can handle the pin inside the loop */
	ResourceOwnerEnlargeBuffers(CurrentResourceOwner);

	for (i = 0; i < NBuffers; i++)
	{
		uint32		buf_state;

		bufHdr = GetBufferDescriptor(i);

		/*
		 * As in DropRelFileNodeBuffers, an unlocked precheck should be safe
		 * and saves some cycles.
		 */
		if (bufHdr->tag.rnode.dbNode != dbid)
			continue;

		ReservePrivateRefCountEntry();

		buf_state = LockBufHdr(bufHdr);
		if (bufHdr->tag.rnode.dbNode == dbid &&
			(buf_state & (BM_VALID | BM_DIRTY)) == (BM_VALID | BM_DIRTY))
		{
			PinBuffer_Locked(bufHdr);
			LWLockAcquire(BufferDescriptorGetContentLock(bufHdr), LW_SHARED);
			FlushBuffer(bufHdr, NULL);
			LWLockRelease(BufferDescriptorGetContentLock(bufHdr));
			UnpinBuffer(bufHdr, true);
		}
		else
			UnlockBufHdr(bufHdr, buf_state);
	}
}