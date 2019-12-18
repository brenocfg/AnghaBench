#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  next; int /*<<< orphan*/  npages; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__ FreePageSpanLeader ;
typedef  int /*<<< orphan*/  FreePageManager ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  fpm_pointer_to_page (char*,TYPE_1__*) ; 
 char* fpm_segment_base (int /*<<< orphan*/ *) ; 
 TYPE_1__* relptr_access (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
FreePageManagerDumpSpans(FreePageManager *fpm, FreePageSpanLeader *span,
						 Size expected_pages, StringInfo buf)
{
	char	   *base = fpm_segment_base(fpm);

	while (span != NULL)
	{
		if (span->npages != expected_pages)
			appendStringInfo(buf, " %zu(%zu)", fpm_pointer_to_page(base, span),
							 span->npages);
		else
			appendStringInfo(buf, " %zu", fpm_pointer_to_page(base, span));
		span = relptr_access(base, span->next);
	}

	appendStringInfoChar(buf, '\n');
}