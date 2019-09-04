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
struct key_vector {scalar_t__ pos; } ;
struct TYPE_2__ {scalar_t__ full_children; scalar_t__ empty_children; } ;

/* Variables and functions */
 scalar_t__ IS_TRIE (struct key_vector*) ; 
 unsigned long child_length (struct key_vector*) ; 
 unsigned long inflate_threshold ; 
 unsigned long inflate_threshold_root ; 
 TYPE_1__* tn_info (struct key_vector*) ; 

__attribute__((used)) static inline bool should_inflate(struct key_vector *tp, struct key_vector *tn)
{
	unsigned long used = child_length(tn);
	unsigned long threshold = used;

	/* Keep root node larger */
	threshold *= IS_TRIE(tp) ? inflate_threshold_root : inflate_threshold;
	used -= tn_info(tn)->empty_children;
	used += tn_info(tn)->full_children;

	/* if bits == KEYLENGTH then pos = 0, and will fail below */

	return (used > 1) && tn->pos && ((50 * used) >= threshold);
}