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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct range_trans {int /*<<< orphan*/  target_class; int /*<<< orphan*/  target_type; int /*<<< orphan*/  source_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  nprim; } ;
struct policydb {int /*<<< orphan*/  process_class; struct class_datum** class_val_to_struct; TYPE_1__ p_classes; int /*<<< orphan*/  range_tr; int /*<<< orphan*/  mls_enabled; } ;
struct mls_range {int dummy; } ;
struct context {int /*<<< orphan*/  type; } ;
struct class_datum {int default_range; } ;

/* Variables and functions */
#define  AVTAB_CHANGE 136 
#define  AVTAB_MEMBER 135 
#define  AVTAB_TRANSITION 134 
#define  DEFAULT_SOURCE_HIGH 133 
#define  DEFAULT_SOURCE_LOW 132 
#define  DEFAULT_SOURCE_LOW_HIGH 131 
#define  DEFAULT_TARGET_HIGH 130 
#define  DEFAULT_TARGET_LOW 129 
#define  DEFAULT_TARGET_LOW_HIGH 128 
 int EINVAL ; 
 struct mls_range* hashtab_search (int /*<<< orphan*/ ,struct range_trans*) ; 
 int mls_context_cpy (struct context*,struct context*) ; 
 int mls_context_cpy_high (struct context*,struct context*) ; 
 int mls_context_cpy_low (struct context*,struct context*) ; 
 int mls_range_set (struct context*,struct mls_range*) ; 

int mls_compute_sid(struct policydb *p,
		    struct context *scontext,
		    struct context *tcontext,
		    u16 tclass,
		    u32 specified,
		    struct context *newcontext,
		    bool sock)
{
	struct range_trans rtr;
	struct mls_range *r;
	struct class_datum *cladatum;
	int default_range = 0;

	if (!p->mls_enabled)
		return 0;

	switch (specified) {
	case AVTAB_TRANSITION:
		/* Look for a range transition rule. */
		rtr.source_type = scontext->type;
		rtr.target_type = tcontext->type;
		rtr.target_class = tclass;
		r = hashtab_search(p->range_tr, &rtr);
		if (r)
			return mls_range_set(newcontext, r);

		if (tclass && tclass <= p->p_classes.nprim) {
			cladatum = p->class_val_to_struct[tclass - 1];
			if (cladatum)
				default_range = cladatum->default_range;
		}

		switch (default_range) {
		case DEFAULT_SOURCE_LOW:
			return mls_context_cpy_low(newcontext, scontext);
		case DEFAULT_SOURCE_HIGH:
			return mls_context_cpy_high(newcontext, scontext);
		case DEFAULT_SOURCE_LOW_HIGH:
			return mls_context_cpy(newcontext, scontext);
		case DEFAULT_TARGET_LOW:
			return mls_context_cpy_low(newcontext, tcontext);
		case DEFAULT_TARGET_HIGH:
			return mls_context_cpy_high(newcontext, tcontext);
		case DEFAULT_TARGET_LOW_HIGH:
			return mls_context_cpy(newcontext, tcontext);
		}

		/* Fallthrough */
	case AVTAB_CHANGE:
		if ((tclass == p->process_class) || (sock == true))
			/* Use the process MLS attributes. */
			return mls_context_cpy(newcontext, scontext);
		else
			/* Use the process effective MLS attributes. */
			return mls_context_cpy_low(newcontext, scontext);
	case AVTAB_MEMBER:
		/* Use the process effective MLS attributes. */
		return mls_context_cpy_low(newcontext, scontext);

	/* fall through */
	}
	return -EINVAL;
}