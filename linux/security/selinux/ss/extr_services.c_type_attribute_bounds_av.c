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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct type_datum {int bounds; } ;
struct policydb {struct type_datum** type_val_to_struct; } ;
struct context {int type; } ;
struct av_decision {int allowed; } ;
typedef  int /*<<< orphan*/  lo_tcontext ;
typedef  int /*<<< orphan*/  lo_scontext ;
typedef  int /*<<< orphan*/  lo_avd ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  context_struct_compute_av (struct policydb*,struct context*,struct context*,int /*<<< orphan*/ ,struct av_decision*,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (struct context*,struct context*,int) ; 
 int /*<<< orphan*/  memset (struct av_decision*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_dump_masked_av (struct policydb*,struct context*,struct context*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void type_attribute_bounds_av(struct policydb *policydb,
				     struct context *scontext,
				     struct context *tcontext,
				     u16 tclass,
				     struct av_decision *avd)
{
	struct context lo_scontext;
	struct context lo_tcontext, *tcontextp = tcontext;
	struct av_decision lo_avd;
	struct type_datum *source;
	struct type_datum *target;
	u32 masked = 0;

	source = policydb->type_val_to_struct[scontext->type - 1];
	BUG_ON(!source);

	if (!source->bounds)
		return;

	target = policydb->type_val_to_struct[tcontext->type - 1];
	BUG_ON(!target);

	memset(&lo_avd, 0, sizeof(lo_avd));

	memcpy(&lo_scontext, scontext, sizeof(lo_scontext));
	lo_scontext.type = source->bounds;

	if (target->bounds) {
		memcpy(&lo_tcontext, tcontext, sizeof(lo_tcontext));
		lo_tcontext.type = target->bounds;
		tcontextp = &lo_tcontext;
	}

	context_struct_compute_av(policydb, &lo_scontext,
				  tcontextp,
				  tclass,
				  &lo_avd,
				  NULL);

	masked = ~lo_avd.allowed & avd->allowed;

	if (likely(!masked))
		return;		/* no masked permission */

	/* mask violated permissions */
	avd->allowed &= ~masked;

	/* audit masked permissions */
	security_dump_masked_av(policydb, scontext, tcontext,
				tclass, masked, "bounds");
}