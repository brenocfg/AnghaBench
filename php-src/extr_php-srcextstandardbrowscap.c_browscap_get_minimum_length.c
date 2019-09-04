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
struct TYPE_3__ {size_t prefix_len; scalar_t__* contains_len; } ;
typedef  TYPE_1__ browscap_entry ;

/* Variables and functions */
 int BROWSCAP_NUM_CONTAINS ; 

__attribute__((used)) static inline size_t browscap_get_minimum_length(browscap_entry *entry) {
	size_t len = entry->prefix_len;
	int i;
	for (i = 0; i < BROWSCAP_NUM_CONTAINS; i++) {
		len += entry->contains_len[i];
	}
	return len;
}