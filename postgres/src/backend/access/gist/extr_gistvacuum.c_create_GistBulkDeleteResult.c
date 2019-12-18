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
struct TYPE_3__ {int /*<<< orphan*/  page_set_context; } ;
typedef  TYPE_1__ GistBulkDeleteResult ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  GenerationContextCreate (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static GistBulkDeleteResult *
create_GistBulkDeleteResult(void)
{
	GistBulkDeleteResult *gist_stats;

	gist_stats = (GistBulkDeleteResult *) palloc0(sizeof(GistBulkDeleteResult));
	gist_stats->page_set_context =
		GenerationContextCreate(CurrentMemoryContext,
								"GiST VACUUM page set context",
								16 * 1024);

	return gist_stats;
}