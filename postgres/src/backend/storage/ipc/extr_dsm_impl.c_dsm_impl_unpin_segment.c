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

/* Variables and functions */
#define  DSM_IMPL_WINDOWS 128 
 int /*<<< orphan*/  DUPLICATE_CLOSE_SOURCE ; 
 int /*<<< orphan*/  DuplicateHandle (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FALSE ; 
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
dsm_impl_unpin_segment(dsm_handle handle, void **impl_private)
{
	switch (dynamic_shared_memory_type)
	{
#ifdef USE_DSM_WINDOWS
		case DSM_IMPL_WINDOWS:
			{
				if (*impl_private &&
					!DuplicateHandle(PostmasterHandle, *impl_private,
									 NULL, NULL, 0, FALSE,
									 DUPLICATE_CLOSE_SOURCE))
				{
					char		name[64];

					snprintf(name, 64, "%s.%u", SEGMENT_NAME_PREFIX, handle);
					_dosmaperr(GetLastError());
					ereport(ERROR,
							(errcode_for_dynamic_shared_memory(),
							 errmsg("could not duplicate handle for \"%s\": %m",
									name)));
				}

				*impl_private = NULL;
				break;
			}
#endif
		default:
			break;
	}
}