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
struct jffs2_raw_node_ref {scalar_t__ flash_offset; struct jffs2_raw_node_ref* next_in_ino; } ;

/* Variables and functions */
 scalar_t__ REF_EMPTY_NODE ; 
 scalar_t__ REF_LINK_NODE ; 

__attribute__((used)) static inline struct jffs2_raw_node_ref *ref_next(struct jffs2_raw_node_ref *ref)
{
	ref++;

	/* Link to another block of refs */
	if (ref->flash_offset == REF_LINK_NODE) {
		ref = ref->next_in_ino;
		if (!ref)
			return ref;
	}

	/* End of chain */
	if (ref->flash_offset == REF_EMPTY_NODE)
		return NULL;

	return ref;
}