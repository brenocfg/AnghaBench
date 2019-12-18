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
struct TYPE_4__ {int /*<<< orphan*/  eoh_context; } ;
struct TYPE_5__ {int /*<<< orphan*/ * er_short_term_cxt; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  TYPE_2__ ExpandedRecordHeader ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MemoryContext
get_short_term_cxt(ExpandedRecordHeader *erh)
{
	if (erh->er_short_term_cxt == NULL)
		erh->er_short_term_cxt =
			AllocSetContextCreate(erh->hdr.eoh_context,
								  "expanded record short-term context",
								  ALLOCSET_SMALL_SIZES);
	else
		MemoryContextReset(erh->er_short_term_cxt);
	return erh->er_short_term_cxt;
}