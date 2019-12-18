#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t avail; void* firstfree; int /*<<< orphan*/ * buildCxt; } ;
typedef  TYPE_1__ IspellDict ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 size_t COMPACT_ALLOC_CHUNK ; 
 size_t COMPACT_MAX_REQ ; 
 size_t MAXALIGN (size_t) ; 
 void* palloc0 (size_t) ; 

__attribute__((used)) static void *
compact_palloc0(IspellDict *Conf, size_t size)
{
	void	   *result;

	/* Should only be called during init */
	Assert(Conf->buildCxt != NULL);

	/* No point in this for large chunks */
	if (size > COMPACT_MAX_REQ)
		return palloc0(size);

	/* Keep everything maxaligned */
	size = MAXALIGN(size);

	/* Need more space? */
	if (size > Conf->avail)
	{
		Conf->firstfree = palloc0(COMPACT_ALLOC_CHUNK);
		Conf->avail = COMPACT_ALLOC_CHUNK;
	}

	result = (void *) Conf->firstfree;
	Conf->firstfree += size;
	Conf->avail -= size;

	return result;
}