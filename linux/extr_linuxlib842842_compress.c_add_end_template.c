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
struct sw842_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_BITS ; 
 int /*<<< orphan*/  OP_END ; 
 int add_bits (struct sw842_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ sw842_template_counts ; 
 int /*<<< orphan*/  template_end_count ; 

__attribute__((used)) static int add_end_template(struct sw842_param *p)
{
	int ret = add_bits(p, OP_END, OP_BITS);

	if (ret)
		return ret;

	if (sw842_template_counts)
		atomic_inc(&template_end_count);

	return 0;
}