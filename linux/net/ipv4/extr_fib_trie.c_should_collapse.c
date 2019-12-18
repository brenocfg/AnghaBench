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
struct key_vector {scalar_t__ bits; } ;
struct TYPE_2__ {scalar_t__ full_children; scalar_t__ empty_children; } ;

/* Variables and functions */
 scalar_t__ KEYLENGTH ; 
 scalar_t__ KEY_MAX ; 
 unsigned long child_length (struct key_vector*) ; 
 TYPE_1__* tn_info (struct key_vector*) ; 

__attribute__((used)) static inline bool should_collapse(struct key_vector *tn)
{
	unsigned long used = child_length(tn);

	used -= tn_info(tn)->empty_children;

	/* account for bits == KEYLENGTH case */
	if ((tn->bits == KEYLENGTH) && tn_info(tn)->full_children)
		used -= KEY_MAX;

	/* One child or none, time to drop us from the trie */
	return used < 2;
}