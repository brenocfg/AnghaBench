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
typedef  int dsm_handle ;
typedef  void* HANDLE ;

/* Variables and functions */
#define  DSM_IMPL_WINDOWS 128 
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int /*<<< orphan*/  DuplicateHandle (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PostmasterHandle ; 
 char* SEGMENT_NAME_PREFIX ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 
 int dynamic_shared_memory_type ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_dynamic_shared_memory () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

void
dsm_impl_pin_segment(dsm_handle handle, void *impl_private,
					 void **impl_private_pm_handle)
{
	switch (dynamic_shared_memory_type)
	{
#ifdef USE_DSM_WINDOWS
		case DSM_IMPL_WINDOWS:
			{
				HANDLE		hmap;

				if (!DuplicateHandle(GetCurrentProcess(), impl_private,
									 PostmasterHandle, &hmap, 0, FALSE,
									 DUPLICATE_SAME_ACCESS))
				{
					char		name[64];

					snprintf(name, 64, "%s.%u", SEGMENT_NAME_PREFIX, handle);
					_dosmaperr(GetLastError());
					ereport(ERROR,
							(errcode_for_dynamic_shared_memory(),
							 errmsg("could not duplicate handle for \"%s\": %m",
									name)));
				}

				/*
				 * Here, we remember the handle that we created in the
				 * postmaster process.  This handle isn't actually usable in
				 * any process other than the postmaster, but that doesn't
				 * matter.  We're just holding onto it so that, if the segment
				 * is unpinned, dsm_impl_unpin_segment can close it.
				 */
				*impl_private_pm_handle = hmap;
				break;
			}
#endif
		default:
			break;
	}
}