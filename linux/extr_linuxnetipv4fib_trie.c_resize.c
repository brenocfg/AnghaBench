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
struct trie {int dummy; } ;
struct key_vector {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_WORK ; 
 struct key_vector* collapse (struct trie*,struct key_vector*) ; 
 struct key_vector* get_child (struct key_vector*,unsigned long) ; 
 unsigned long get_index (int /*<<< orphan*/ ,struct key_vector*) ; 
 struct key_vector* halve (struct trie*,struct key_vector*) ; 
 int /*<<< orphan*/  halve_threshold ; 
 struct key_vector* inflate (struct trie*,struct key_vector*) ; 
 int /*<<< orphan*/  inflate_threshold ; 
 struct key_vector* node_parent (struct key_vector*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct key_vector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ should_collapse (struct key_vector*) ; 
 scalar_t__ should_halve (struct key_vector*,struct key_vector*) ; 
 scalar_t__ should_inflate (struct key_vector*,struct key_vector*) ; 

__attribute__((used)) static struct key_vector *resize(struct trie *t, struct key_vector *tn)
{
#ifdef CONFIG_IP_FIB_TRIE_STATS
	struct trie_use_stats __percpu *stats = t->stats;
#endif
	struct key_vector *tp = node_parent(tn);
	unsigned long cindex = get_index(tn->key, tp);
	int max_work = MAX_WORK;

	pr_debug("In tnode_resize %p inflate_threshold=%d threshold=%d\n",
		 tn, inflate_threshold, halve_threshold);

	/* track the tnode via the pointer from the parent instead of
	 * doing it ourselves.  This way we can let RCU fully do its
	 * thing without us interfering
	 */
	BUG_ON(tn != get_child(tp, cindex));

	/* Double as long as the resulting node has a number of
	 * nonempty nodes that are above the threshold.
	 */
	while (should_inflate(tp, tn) && max_work) {
		tp = inflate(t, tn);
		if (!tp) {
#ifdef CONFIG_IP_FIB_TRIE_STATS
			this_cpu_inc(stats->resize_node_skipped);
#endif
			break;
		}

		max_work--;
		tn = get_child(tp, cindex);
	}

	/* update parent in case inflate failed */
	tp = node_parent(tn);

	/* Return if at least one inflate is run */
	if (max_work != MAX_WORK)
		return tp;

	/* Halve as long as the number of empty children in this
	 * node is above threshold.
	 */
	while (should_halve(tp, tn) && max_work) {
		tp = halve(t, tn);
		if (!tp) {
#ifdef CONFIG_IP_FIB_TRIE_STATS
			this_cpu_inc(stats->resize_node_skipped);
#endif
			break;
		}

		max_work--;
		tn = get_child(tp, cindex);
	}

	/* Only one child remains */
	if (should_collapse(tn))
		return collapse(t, tn);

	/* update parent in case halve failed */
	return node_parent(tn);
}