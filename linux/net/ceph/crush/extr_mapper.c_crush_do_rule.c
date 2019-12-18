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
struct crush_work {int dummy; } ;
struct crush_rule_step {int op; int arg1; int /*<<< orphan*/  arg2; } ;
struct crush_rule {scalar_t__ len; struct crush_rule_step* steps; } ;
struct crush_map {int working_size; int choose_total_tries; int choose_local_tries; int choose_local_fallback_tries; int chooseleaf_vary_r; int chooseleaf_stable; scalar_t__ max_rules; int max_devices; int max_buckets; int /*<<< orphan*/ * buckets; int /*<<< orphan*/  chooseleaf_descend_once; struct crush_rule** rules; } ;
struct crush_choose_arg {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
#define  CRUSH_RULE_CHOOSELEAF_FIRSTN 139 
#define  CRUSH_RULE_CHOOSELEAF_INDEP 138 
#define  CRUSH_RULE_CHOOSE_FIRSTN 137 
#define  CRUSH_RULE_CHOOSE_INDEP 136 
#define  CRUSH_RULE_EMIT 135 
#define  CRUSH_RULE_SET_CHOOSELEAF_STABLE 134 
#define  CRUSH_RULE_SET_CHOOSELEAF_TRIES 133 
#define  CRUSH_RULE_SET_CHOOSELEAF_VARY_R 132 
#define  CRUSH_RULE_SET_CHOOSE_LOCAL_FALLBACK_TRIES 131 
#define  CRUSH_RULE_SET_CHOOSE_LOCAL_TRIES 130 
#define  CRUSH_RULE_SET_CHOOSE_TRIES 129 
#define  CRUSH_RULE_TAKE 128 
 int crush_choose_firstn (struct crush_map const*,struct crush_work*,int /*<<< orphan*/ ,scalar_t__ const*,int,int,int,int /*<<< orphan*/ ,int*,int,int,int,int,int,int,int,int,int,int*,int /*<<< orphan*/ ,struct crush_choose_arg const*) ; 
 int /*<<< orphan*/  crush_choose_indep (struct crush_map const*,struct crush_work*,int /*<<< orphan*/ ,scalar_t__ const*,int,int,int,int,int /*<<< orphan*/ ,int*,int,int,int,int,int*,int /*<<< orphan*/ ,struct crush_choose_arg const*) ; 
 int /*<<< orphan*/  dprintk (char*,int const,...) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int crush_do_rule(const struct crush_map *map,
		  int ruleno, int x, int *result, int result_max,
		  const __u32 *weight, int weight_max,
		  void *cwin, const struct crush_choose_arg *choose_args)
{
	int result_len;
	struct crush_work *cw = cwin;
	int *a = cwin + map->working_size;
	int *b = a + result_max;
	int *c = b + result_max;
	int *w = a;
	int *o = b;
	int recurse_to_leaf;
	int wsize = 0;
	int osize;
	int *tmp;
	const struct crush_rule *rule;
	__u32 step;
	int i, j;
	int numrep;
	int out_size;
	/*
	 * the original choose_total_tries value was off by one (it
	 * counted "retries" and not "tries").  add one.
	 */
	int choose_tries = map->choose_total_tries + 1;
	int choose_leaf_tries = 0;
	/*
	 * the local tries values were counted as "retries", though,
	 * and need no adjustment
	 */
	int choose_local_retries = map->choose_local_tries;
	int choose_local_fallback_retries = map->choose_local_fallback_tries;

	int vary_r = map->chooseleaf_vary_r;
	int stable = map->chooseleaf_stable;

	if ((__u32)ruleno >= map->max_rules) {
		dprintk(" bad ruleno %d\n", ruleno);
		return 0;
	}

	rule = map->rules[ruleno];
	result_len = 0;

	for (step = 0; step < rule->len; step++) {
		int firstn = 0;
		const struct crush_rule_step *curstep = &rule->steps[step];

		switch (curstep->op) {
		case CRUSH_RULE_TAKE:
			if ((curstep->arg1 >= 0 &&
			     curstep->arg1 < map->max_devices) ||
			    (-1-curstep->arg1 >= 0 &&
			     -1-curstep->arg1 < map->max_buckets &&
			     map->buckets[-1-curstep->arg1])) {
				w[0] = curstep->arg1;
				wsize = 1;
			} else {
				dprintk(" bad take value %d\n", curstep->arg1);
			}
			break;

		case CRUSH_RULE_SET_CHOOSE_TRIES:
			if (curstep->arg1 > 0)
				choose_tries = curstep->arg1;
			break;

		case CRUSH_RULE_SET_CHOOSELEAF_TRIES:
			if (curstep->arg1 > 0)
				choose_leaf_tries = curstep->arg1;
			break;

		case CRUSH_RULE_SET_CHOOSE_LOCAL_TRIES:
			if (curstep->arg1 >= 0)
				choose_local_retries = curstep->arg1;
			break;

		case CRUSH_RULE_SET_CHOOSE_LOCAL_FALLBACK_TRIES:
			if (curstep->arg1 >= 0)
				choose_local_fallback_retries = curstep->arg1;
			break;

		case CRUSH_RULE_SET_CHOOSELEAF_VARY_R:
			if (curstep->arg1 >= 0)
				vary_r = curstep->arg1;
			break;

		case CRUSH_RULE_SET_CHOOSELEAF_STABLE:
			if (curstep->arg1 >= 0)
				stable = curstep->arg1;
			break;

		case CRUSH_RULE_CHOOSELEAF_FIRSTN:
		case CRUSH_RULE_CHOOSE_FIRSTN:
			firstn = 1;
			/* fall through */
		case CRUSH_RULE_CHOOSELEAF_INDEP:
		case CRUSH_RULE_CHOOSE_INDEP:
			if (wsize == 0)
				break;

			recurse_to_leaf =
				curstep->op ==
				 CRUSH_RULE_CHOOSELEAF_FIRSTN ||
				curstep->op ==
				CRUSH_RULE_CHOOSELEAF_INDEP;

			/* reset output */
			osize = 0;

			for (i = 0; i < wsize; i++) {
				int bno;
				numrep = curstep->arg1;
				if (numrep <= 0) {
					numrep += result_max;
					if (numrep <= 0)
						continue;
				}
				j = 0;
				/* make sure bucket id is valid */
				bno = -1 - w[i];
				if (bno < 0 || bno >= map->max_buckets) {
					/* w[i] is probably CRUSH_ITEM_NONE */
					dprintk("  bad w[i] %d\n", w[i]);
					continue;
				}
				if (firstn) {
					int recurse_tries;
					if (choose_leaf_tries)
						recurse_tries =
							choose_leaf_tries;
					else if (map->chooseleaf_descend_once)
						recurse_tries = 1;
					else
						recurse_tries = choose_tries;
					osize += crush_choose_firstn(
						map,
						cw,
						map->buckets[bno],
						weight, weight_max,
						x, numrep,
						curstep->arg2,
						o+osize, j,
						result_max-osize,
						choose_tries,
						recurse_tries,
						choose_local_retries,
						choose_local_fallback_retries,
						recurse_to_leaf,
						vary_r,
						stable,
						c+osize,
						0,
						choose_args);
				} else {
					out_size = ((numrep < (result_max-osize)) ?
						    numrep : (result_max-osize));
					crush_choose_indep(
						map,
						cw,
						map->buckets[bno],
						weight, weight_max,
						x, out_size, numrep,
						curstep->arg2,
						o+osize, j,
						choose_tries,
						choose_leaf_tries ?
						   choose_leaf_tries : 1,
						recurse_to_leaf,
						c+osize,
						0,
						choose_args);
					osize += out_size;
				}
			}

			if (recurse_to_leaf)
				/* copy final _leaf_ values to output set */
				memcpy(o, c, osize*sizeof(*o));

			/* swap o and w arrays */
			tmp = o;
			o = w;
			w = tmp;
			wsize = osize;
			break;


		case CRUSH_RULE_EMIT:
			for (i = 0; i < wsize && result_len < result_max; i++) {
				result[result_len] = w[i];
				result_len++;
			}
			wsize = 0;
			break;

		default:
			dprintk(" unknown op %d at step %d\n",
				curstep->op, step);
			break;
		}
	}

	return result_len;
}