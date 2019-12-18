#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_5__ {int /*<<< orphan*/  blockNum; int /*<<< orphan*/  forkNum; int /*<<< orphan*/  rnode; } ;
struct TYPE_6__ {TYPE_1__ tag; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ BufferDesc ;
typedef  int Buffer ;
typedef  int /*<<< orphan*/  BackendId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int BUF_FLAG_MASK ; 
 int /*<<< orphan*/  BUF_STATE_GET_REFCOUNT (int) ; 
 scalar_t__ BufferIsLocal (int) ; 
 int /*<<< orphan*/  BufferIsValid (int) ; 
 TYPE_2__* GetBufferDescriptor (int) ; 
 TYPE_2__* GetLocalBufferDescriptor (int) ; 
 int /*<<< orphan*/  GetPrivateRefCount (int) ; 
 int /*<<< orphan*/  InvalidBackendId ; 
 int /*<<< orphan*/ * LocalRefCount ; 
 int /*<<< orphan*/  MyBackendId ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 
 char* relpathbackend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
PrintBufferLeakWarning(Buffer buffer)
{
	BufferDesc *buf;
	int32		loccount;
	char	   *path;
	BackendId	backend;
	uint32		buf_state;

	Assert(BufferIsValid(buffer));
	if (BufferIsLocal(buffer))
	{
		buf = GetLocalBufferDescriptor(-buffer - 1);
		loccount = LocalRefCount[-buffer - 1];
		backend = MyBackendId;
	}
	else
	{
		buf = GetBufferDescriptor(buffer - 1);
		loccount = GetPrivateRefCount(buffer);
		backend = InvalidBackendId;
	}

	/* theoretically we should lock the bufhdr here */
	path = relpathbackend(buf->tag.rnode, backend, buf->tag.forkNum);
	buf_state = pg_atomic_read_u32(&buf->state);
	elog(WARNING,
		 "buffer refcount leak: [%03d] "
		 "(rel=%s, blockNum=%u, flags=0x%x, refcount=%u %d)",
		 buffer, path,
		 buf->tag.blockNum, buf_state & BUF_FLAG_MASK,
		 BUF_STATE_GET_REFCOUNT(buf_state), loccount);
	pfree(path);
}