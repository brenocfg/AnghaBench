#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_18__ {int /*<<< orphan*/ * pagemap; int /*<<< orphan*/  fpm; } ;
typedef  TYPE_2__ dsa_segment_map ;
typedef  int /*<<< orphan*/  dsa_pointer ;
typedef  int /*<<< orphan*/  dsa_area_pool ;
struct TYPE_19__ {TYPE_1__* control; } ;
typedef  TYPE_3__ dsa_area ;
struct TYPE_17__ {int /*<<< orphan*/ * pools; } ;

/* Variables and functions */
 int /*<<< orphan*/  AllocHugeSizeIsValid (size_t) ; 
 int /*<<< orphan*/  AllocSizeIsValid (size_t) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int DSA_ALLOC_HUGE ; 
 int DSA_ALLOC_NO_OOM ; 
 int DSA_ALLOC_ZERO ; 
 int /*<<< orphan*/  DSA_AREA_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  DSA_MAKE_POINTER (int /*<<< orphan*/ ,size_t) ; 
 int DSA_SCLASS_BLOCK_OF_SPANS ; 
 int /*<<< orphan*/  DSA_SCLASS_LOCK (TYPE_3__*,size_t) ; 
 size_t DSA_SCLASS_SPAN_LARGE ; 
 size_t DSA_SIZE_CLASS_MAP_QUANTUM ; 
 int /*<<< orphan*/  DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 size_t FPM_PAGE_SIZE ; 
 int /*<<< orphan*/  FreePageManagerGet (int /*<<< orphan*/ ,size_t,size_t*) ; 
 int /*<<< orphan*/  InvalidDsaPointer ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  alloc_object (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dsa_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_get_address (TYPE_3__*,int /*<<< orphan*/ ) ; 
 size_t* dsa_size_class_map ; 
 size_t* dsa_size_classes ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,size_t) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 size_t fpm_size_to_pages (size_t) ; 
 TYPE_2__* get_best_segment (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  get_segment_index (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  init_span (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t) ; 
 int lengthof (size_t*) ; 
 TYPE_2__* make_new_segment (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

dsa_pointer
dsa_allocate_extended(dsa_area *area, size_t size, int flags)
{
	uint16		size_class;
	dsa_pointer start_pointer;
	dsa_segment_map *segment_map;
	dsa_pointer result;

	Assert(size > 0);

	/* Sanity check on huge individual allocation size. */
	if (((flags & DSA_ALLOC_HUGE) != 0 && !AllocHugeSizeIsValid(size)) ||
		((flags & DSA_ALLOC_HUGE) == 0 && !AllocSizeIsValid(size)))
		elog(ERROR, "invalid DSA memory alloc request size %zu", size);

	/*
	 * If bigger than the largest size class, just grab a run of pages from
	 * the free page manager, instead of allocating an object from a pool.
	 * There will still be a span, but it's a special class of span that
	 * manages this whole allocation and simply gives all pages back to the
	 * free page manager when dsa_free is called.
	 */
	if (size > dsa_size_classes[lengthof(dsa_size_classes) - 1])
	{
		size_t		npages = fpm_size_to_pages(size);
		size_t		first_page;
		dsa_pointer span_pointer;
		dsa_area_pool *pool = &area->control->pools[DSA_SCLASS_SPAN_LARGE];

		/* Obtain a span object. */
		span_pointer = alloc_object(area, DSA_SCLASS_BLOCK_OF_SPANS);
		if (!DsaPointerIsValid(span_pointer))
		{
			/* Raise error unless asked not to. */
			if ((flags & DSA_ALLOC_NO_OOM) == 0)
				ereport(ERROR,
						(errcode(ERRCODE_OUT_OF_MEMORY),
						 errmsg("out of memory"),
						 errdetail("Failed on DSA request of size %zu.",
								   size)));
			return InvalidDsaPointer;
		}

		LWLockAcquire(DSA_AREA_LOCK(area), LW_EXCLUSIVE);

		/* Find a segment from which to allocate. */
		segment_map = get_best_segment(area, npages);
		if (segment_map == NULL)
			segment_map = make_new_segment(area, npages);
		if (segment_map == NULL)
		{
			/* Can't make any more segments: game over. */
			LWLockRelease(DSA_AREA_LOCK(area));
			dsa_free(area, span_pointer);

			/* Raise error unless asked not to. */
			if ((flags & DSA_ALLOC_NO_OOM) == 0)
				ereport(ERROR,
						(errcode(ERRCODE_OUT_OF_MEMORY),
						 errmsg("out of memory"),
						 errdetail("Failed on DSA request of size %zu.",
								   size)));
			return InvalidDsaPointer;
		}

		/*
		 * Ask the free page manager for a run of pages.  This should always
		 * succeed, since both get_best_segment and make_new_segment should
		 * only return a non-NULL pointer if it actually contains enough
		 * contiguous freespace.  If it does fail, something in our backend
		 * private state is out of whack, so use FATAL to kill the process.
		 */
		if (!FreePageManagerGet(segment_map->fpm, npages, &first_page))
			elog(FATAL,
				 "dsa_allocate could not find %zu free pages", npages);
		LWLockRelease(DSA_AREA_LOCK(area));

		start_pointer = DSA_MAKE_POINTER(get_segment_index(area, segment_map),
										 first_page * FPM_PAGE_SIZE);

		/* Initialize span and pagemap. */
		LWLockAcquire(DSA_SCLASS_LOCK(area, DSA_SCLASS_SPAN_LARGE),
					  LW_EXCLUSIVE);
		init_span(area, span_pointer, pool, start_pointer, npages,
				  DSA_SCLASS_SPAN_LARGE);
		segment_map->pagemap[first_page] = span_pointer;
		LWLockRelease(DSA_SCLASS_LOCK(area, DSA_SCLASS_SPAN_LARGE));

		/* Zero-initialize the memory if requested. */
		if ((flags & DSA_ALLOC_ZERO) != 0)
			memset(dsa_get_address(area, start_pointer), 0, size);

		return start_pointer;
	}

	/* Map allocation to a size class. */
	if (size < lengthof(dsa_size_class_map) * DSA_SIZE_CLASS_MAP_QUANTUM)
	{
		int			mapidx;

		/* For smaller sizes we have a lookup table... */
		mapidx = ((size + DSA_SIZE_CLASS_MAP_QUANTUM - 1) /
				  DSA_SIZE_CLASS_MAP_QUANTUM) - 1;
		size_class = dsa_size_class_map[mapidx];
	}
	else
	{
		uint16		min;
		uint16		max;

		/* ... and for the rest we search by binary chop. */
		min = dsa_size_class_map[lengthof(dsa_size_class_map) - 1];
		max = lengthof(dsa_size_classes) - 1;

		while (min < max)
		{
			uint16		mid = (min + max) / 2;
			uint16		class_size = dsa_size_classes[mid];

			if (class_size < size)
				min = mid + 1;
			else
				max = mid;
		}

		size_class = min;
	}
	Assert(size <= dsa_size_classes[size_class]);
	Assert(size_class == 0 || size > dsa_size_classes[size_class - 1]);

	/* Attempt to allocate an object from the appropriate pool. */
	result = alloc_object(area, size_class);

	/* Check for failure to allocate. */
	if (!DsaPointerIsValid(result))
	{
		/* Raise error unless asked not to. */
		if ((flags & DSA_ALLOC_NO_OOM) == 0)
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory"),
					 errdetail("Failed on DSA request of size %zu.", size)));
		return InvalidDsaPointer;
	}

	/* Zero-initialize the memory if requested. */
	if ((flags & DSA_ALLOC_ZERO) != 0)
		memset(dsa_get_address(area, result), 0, size);

	return result;
}