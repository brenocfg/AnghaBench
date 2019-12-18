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
typedef  scalar_t__ dsm_op ;
typedef  int /*<<< orphan*/  dsm_handle ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  DSM_IMPL_MMAP 131 
#define  DSM_IMPL_POSIX 130 
#define  DSM_IMPL_SYSV 129 
#define  DSM_IMPL_WINDOWS 128 
 scalar_t__ DSM_OP_ATTACH ; 
 scalar_t__ DSM_OP_CREATE ; 
 int /*<<< orphan*/  ERROR ; 
 int dsm_impl_mmap (scalar_t__,int /*<<< orphan*/ ,scalar_t__,void**,void**,scalar_t__*,int) ; 
 int dsm_impl_posix (scalar_t__,int /*<<< orphan*/ ,scalar_t__,void**,void**,scalar_t__*,int) ; 
 int dsm_impl_sysv (scalar_t__,int /*<<< orphan*/ ,scalar_t__,void**,void**,scalar_t__*,int) ; 
 int dsm_impl_windows (scalar_t__,int /*<<< orphan*/ ,scalar_t__,void**,void**,scalar_t__*,int) ; 
 int dynamic_shared_memory_type ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

bool
dsm_impl_op(dsm_op op, dsm_handle handle, Size request_size,
			void **impl_private, void **mapped_address, Size *mapped_size,
			int elevel)
{
	Assert(op == DSM_OP_CREATE || request_size == 0);
	Assert((op != DSM_OP_CREATE && op != DSM_OP_ATTACH) ||
		   (*mapped_address == NULL && *mapped_size == 0));

	switch (dynamic_shared_memory_type)
	{
#ifdef USE_DSM_POSIX
		case DSM_IMPL_POSIX:
			return dsm_impl_posix(op, handle, request_size, impl_private,
								  mapped_address, mapped_size, elevel);
#endif
#ifdef USE_DSM_SYSV
		case DSM_IMPL_SYSV:
			return dsm_impl_sysv(op, handle, request_size, impl_private,
								 mapped_address, mapped_size, elevel);
#endif
#ifdef USE_DSM_WINDOWS
		case DSM_IMPL_WINDOWS:
			return dsm_impl_windows(op, handle, request_size, impl_private,
									mapped_address, mapped_size, elevel);
#endif
#ifdef USE_DSM_MMAP
		case DSM_IMPL_MMAP:
			return dsm_impl_mmap(op, handle, request_size, impl_private,
								 mapped_address, mapped_size, elevel);
#endif
		default:
			elog(ERROR, "unexpected dynamic shared memory type: %d",
				 dynamic_shared_memory_type);
			return false;
	}
}