#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shm_toc_estimator ;
typedef  int /*<<< orphan*/  shm_toc ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  dsm_handle ;
typedef  int /*<<< orphan*/  dsa_area ;
struct TYPE_2__ {int /*<<< orphan*/ * area; int /*<<< orphan*/ * segment; } ;
typedef  int /*<<< orphan*/  SharedRecordTypmodRegistry ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 TYPE_1__* CurrentSession ; 
 int /*<<< orphan*/  DSM_CREATE_NULL_IF_MAXSEGMENTS ; 
 int /*<<< orphan*/  DSM_HANDLE_INVALID ; 
 int /*<<< orphan*/  LWTRANCHE_SESSION_DSA ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 size_t SESSION_DSA_SIZE ; 
 int /*<<< orphan*/  SESSION_KEY_DSA ; 
 int /*<<< orphan*/  SESSION_KEY_RECORD_TYPMOD_REGISTRY ; 
 int /*<<< orphan*/  SESSION_MAGIC ; 
 size_t SharedRecordTypmodRegistryEstimate () ; 
 int /*<<< orphan*/  SharedRecordTypmodRegistryInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ * dsa_create_in_place (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_pin_mapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsm_create (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_pin_mapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_handle (int /*<<< orphan*/ *) ; 
 void* shm_toc_allocate (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * shm_toc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t shm_toc_estimate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_toc_estimate_chunk (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  shm_toc_estimate_keys (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shm_toc_initialize_estimator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_toc_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

dsm_handle
GetSessionDsmHandle(void)
{
	shm_toc_estimator estimator;
	shm_toc    *toc;
	dsm_segment *seg;
	size_t		typmod_registry_size;
	size_t		size;
	void	   *dsa_space;
	void	   *typmod_registry_space;
	dsa_area   *dsa;
	MemoryContext old_context;

	/*
	 * If we have already created a session-scope DSM segment in this backend,
	 * return its handle.  The same segment will be used for the rest of this
	 * backend's lifetime.
	 */
	if (CurrentSession->segment != NULL)
		return dsm_segment_handle(CurrentSession->segment);

	/* Otherwise, prepare to set one up. */
	old_context = MemoryContextSwitchTo(TopMemoryContext);
	shm_toc_initialize_estimator(&estimator);

	/* Estimate space for the per-session DSA area. */
	shm_toc_estimate_keys(&estimator, 1);
	shm_toc_estimate_chunk(&estimator, SESSION_DSA_SIZE);

	/* Estimate space for the per-session record typmod registry. */
	typmod_registry_size = SharedRecordTypmodRegistryEstimate();
	shm_toc_estimate_keys(&estimator, 1);
	shm_toc_estimate_chunk(&estimator, typmod_registry_size);

	/* Set up segment and TOC. */
	size = shm_toc_estimate(&estimator);
	seg = dsm_create(size, DSM_CREATE_NULL_IF_MAXSEGMENTS);
	if (seg == NULL)
	{
		MemoryContextSwitchTo(old_context);

		return DSM_HANDLE_INVALID;
	}
	toc = shm_toc_create(SESSION_MAGIC,
						 dsm_segment_address(seg),
						 size);

	/* Create per-session DSA area. */
	dsa_space = shm_toc_allocate(toc, SESSION_DSA_SIZE);
	dsa = dsa_create_in_place(dsa_space,
							  SESSION_DSA_SIZE,
							  LWTRANCHE_SESSION_DSA,
							  seg);
	shm_toc_insert(toc, SESSION_KEY_DSA, dsa_space);


	/* Create session-scoped shared record typmod registry. */
	typmod_registry_space = shm_toc_allocate(toc, typmod_registry_size);
	SharedRecordTypmodRegistryInit((SharedRecordTypmodRegistry *)
								   typmod_registry_space, seg, dsa);
	shm_toc_insert(toc, SESSION_KEY_RECORD_TYPMOD_REGISTRY,
				   typmod_registry_space);

	/*
	 * If we got this far, we can pin the shared memory so it stays mapped for
	 * the rest of this backend's life.  If we don't make it this far, cleanup
	 * callbacks for anything we installed above (ie currently
	 * SharedRecordTypmodRegistry) will run when the DSM segment is detached
	 * by CurrentResourceOwner so we aren't left with a broken CurrentSession.
	 */
	dsm_pin_mapping(seg);
	dsa_pin_mapping(dsa);

	/* Make segment and area available via CurrentSession. */
	CurrentSession->segment = seg;
	CurrentSession->area = dsa;

	MemoryContextSwitchTo(old_context);

	return dsm_segment_handle(seg);
}