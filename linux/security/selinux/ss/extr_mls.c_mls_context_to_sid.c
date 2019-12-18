#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sidtab {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct policydb {TYPE_3__ p_cats; TYPE_1__ p_levels; int /*<<< orphan*/  mls_enabled; } ;
struct level_datum {TYPE_2__* level; } ;
struct TYPE_10__ {TYPE_4__* level; } ;
struct context {TYPE_5__ range; } ;
struct cat_datum {int value; } ;
struct TYPE_9__ {int /*<<< orphan*/  cat; int /*<<< orphan*/  sens; } ;
struct TYPE_7__ {int /*<<< orphan*/  sens; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SECSID_NULL ; 
 int ebitmap_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ebitmap_set_bit (int /*<<< orphan*/ *,int,int) ; 
 void* hashtab_search (int /*<<< orphan*/ ,char*) ; 
 int mls_context_cpy (struct context*,struct context*) ; 
 struct context* sidtab_search (struct sidtab*,scalar_t__) ; 
 char* strchr (char*,char) ; 

int mls_context_to_sid(struct policydb *pol,
		       char oldc,
		       char *scontext,
		       struct context *context,
		       struct sidtab *s,
		       u32 def_sid)
{
	char *sensitivity, *cur_cat, *next_cat, *rngptr;
	struct level_datum *levdatum;
	struct cat_datum *catdatum, *rngdatum;
	int l, rc, i;
	char *rangep[2];

	if (!pol->mls_enabled) {
		/*
		 * With no MLS, only return -EINVAL if there is a MLS field
		 * and it did not come from an xattr.
		 */
		if (oldc && def_sid == SECSID_NULL)
			return -EINVAL;
		return 0;
	}

	/*
	 * No MLS component to the security context, try and map to
	 * default if provided.
	 */
	if (!oldc) {
		struct context *defcon;

		if (def_sid == SECSID_NULL)
			return -EINVAL;

		defcon = sidtab_search(s, def_sid);
		if (!defcon)
			return -EINVAL;

		return mls_context_cpy(context, defcon);
	}

	/*
	 * If we're dealing with a range, figure out where the two parts
	 * of the range begin.
	 */
	rangep[0] = scontext;
	rangep[1] = strchr(scontext, '-');
	if (rangep[1]) {
		rangep[1][0] = '\0';
		rangep[1]++;
	}

	/* For each part of the range: */
	for (l = 0; l < 2; l++) {
		/* Split sensitivity and category set. */
		sensitivity = rangep[l];
		if (sensitivity == NULL)
			break;
		next_cat = strchr(sensitivity, ':');
		if (next_cat)
			*(next_cat++) = '\0';

		/* Parse sensitivity. */
		levdatum = hashtab_search(pol->p_levels.table, sensitivity);
		if (!levdatum)
			return -EINVAL;
		context->range.level[l].sens = levdatum->level->sens;

		/* Extract category set. */
		while (next_cat != NULL) {
			cur_cat = next_cat;
			next_cat = strchr(next_cat, ',');
			if (next_cat != NULL)
				*(next_cat++) = '\0';

			/* Separate into range if exists */
			rngptr = strchr(cur_cat, '.');
			if (rngptr != NULL) {
				/* Remove '.' */
				*rngptr++ = '\0';
			}

			catdatum = hashtab_search(pol->p_cats.table, cur_cat);
			if (!catdatum)
				return -EINVAL;

			rc = ebitmap_set_bit(&context->range.level[l].cat,
					     catdatum->value - 1, 1);
			if (rc)
				return rc;

			/* If range, set all categories in range */
			if (rngptr == NULL)
				continue;

			rngdatum = hashtab_search(pol->p_cats.table, rngptr);
			if (!rngdatum)
				return -EINVAL;

			if (catdatum->value >= rngdatum->value)
				return -EINVAL;

			for (i = catdatum->value; i < rngdatum->value; i++) {
				rc = ebitmap_set_bit(&context->range.level[l].cat, i, 1);
				if (rc)
					return rc;
			}
		}
	}

	/* If we didn't see a '-', the range start is also the range end. */
	if (rangep[1] == NULL) {
		context->range.level[1].sens = context->range.level[0].sens;
		rc = ebitmap_cpy(&context->range.level[1].cat,
				 &context->range.level[0].cat);
		if (rc)
			return rc;
	}

	return 0;
}