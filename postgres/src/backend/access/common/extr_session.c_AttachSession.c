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
typedef  int /*<<< orphan*/  shm_toc ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  dsm_handle ;
typedef  int /*<<< orphan*/  dsa_area ;
struct TYPE_2__ {int /*<<< orphan*/ * area; int /*<<< orphan*/ * segment; } ;
typedef  int /*<<< orphan*/  SharedRecordTypmodRegistry ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 TYPE_1__* CurrentSession ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SESSION_KEY_DSA ; 
 int /*<<< orphan*/  SESSION_KEY_RECORD_TYPMOD_REGISTRY ; 
 int /*<<< orphan*/  SESSION_MAGIC ; 
 int /*<<< orphan*/  SharedRecordTypmodRegistryAttach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ * dsa_attach_in_place (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_pin_mapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsm_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_pin_mapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * shm_toc_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* shm_toc_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
AttachSession(dsm_handle handle)
{
	dsm_segment *seg;
	shm_toc    *toc;
	void	   *dsa_space;
	void	   *typmod_registry_space;
	dsa_area   *dsa;
	MemoryContext old_context;

	old_context = MemoryContextSwitchTo(TopMemoryContext);

	/* Attach to the DSM segment. */
	seg = dsm_attach(handle);
	if (seg == NULL)
		elog(ERROR, "could not attach to per-session DSM segment");
	toc = shm_toc_attach(SESSION_MAGIC, dsm_segment_address(seg));

	/* Attach to the DSA area. */
	dsa_space = shm_toc_lookup(toc, SESSION_KEY_DSA, false);
	dsa = dsa_attach_in_place(dsa_space, seg);

	/* Make them available via the current session. */
	CurrentSession->segment = seg;
	CurrentSession->area = dsa;

	/* Attach to the shared record typmod registry. */
	typmod_registry_space =
		shm_toc_lookup(toc, SESSION_KEY_RECORD_TYPMOD_REGISTRY, false);
	SharedRecordTypmodRegistryAttach((SharedRecordTypmodRegistry *)
									 typmod_registry_space);

	/* Remain attached until end of backend or DetachSession(). */
	dsm_pin_mapping(seg);
	dsa_pin_mapping(dsa);

	MemoryContextSwitchTo(old_context);
}