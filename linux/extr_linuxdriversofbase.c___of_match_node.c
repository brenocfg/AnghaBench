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
struct of_device_id {scalar_t__* name; scalar_t__* type; scalar_t__* compatible; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int __of_device_is_compatible (struct device_node const*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static
const struct of_device_id *__of_match_node(const struct of_device_id *matches,
					   const struct device_node *node)
{
	const struct of_device_id *best_match = NULL;
	int score, best_score = 0;

	if (!matches)
		return NULL;

	for (; matches->name[0] || matches->type[0] || matches->compatible[0]; matches++) {
		score = __of_device_is_compatible(node, matches->compatible,
						  matches->type, matches->name);
		if (score > best_score) {
			best_match = matches;
			best_score = score;
		}
	}

	return best_match;
}