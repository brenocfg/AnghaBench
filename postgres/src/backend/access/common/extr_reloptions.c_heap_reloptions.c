#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_3__ {int analyze_threshold; int analyze_scale_factor; } ;
struct TYPE_4__ {int fillfactor; TYPE_1__ autovacuum; } ;
typedef  TYPE_2__ StdRdOptions ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
#define  RELKIND_MATVIEW 130 
#define  RELKIND_RELATION 129 
#define  RELKIND_TOASTVALUE 128 
 int /*<<< orphan*/  RELOPT_KIND_HEAP ; 
 int /*<<< orphan*/  RELOPT_KIND_TOAST ; 
 int /*<<< orphan*/ * default_reloptions (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bytea *
heap_reloptions(char relkind, Datum reloptions, bool validate)
{
	StdRdOptions *rdopts;

	switch (relkind)
	{
		case RELKIND_TOASTVALUE:
			rdopts = (StdRdOptions *)
				default_reloptions(reloptions, validate, RELOPT_KIND_TOAST);
			if (rdopts != NULL)
			{
				/* adjust default-only parameters for TOAST relations */
				rdopts->fillfactor = 100;
				rdopts->autovacuum.analyze_threshold = -1;
				rdopts->autovacuum.analyze_scale_factor = -1;
			}
			return (bytea *) rdopts;
		case RELKIND_RELATION:
		case RELKIND_MATVIEW:
			return default_reloptions(reloptions, validate, RELOPT_KIND_HEAP);
		default:
			/* other relkinds are not supported */
			return NULL;
	}
}