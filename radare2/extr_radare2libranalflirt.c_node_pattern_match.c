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
typedef  scalar_t__ ut8 ;
struct TYPE_3__ {int length; scalar_t__* pattern_bytes; int /*<<< orphan*/ * variant_bool_array; } ;
typedef  TYPE_1__ RFlirtNode ;

/* Variables and functions */

__attribute__((used)) static int node_pattern_match(const RFlirtNode *node, ut8 *b, int buf_size) {
	int i;
	for (i = 0; i < node->length; i++) {
		if (!node->variant_bool_array[i]) {
			if (i < node->length && node->pattern_bytes[i] != b[i]) {
				return false;
			}
		}
	}
	return true;
}