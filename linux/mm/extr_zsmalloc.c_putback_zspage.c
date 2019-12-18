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
struct zspage {int dummy; } ;
struct size_class {int /*<<< orphan*/  index; } ;
typedef  enum fullness_group { ____Placeholder_fullness_group } fullness_group ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int get_fullness_group (struct size_class*,struct zspage*) ; 
 int /*<<< orphan*/  insert_zspage (struct size_class*,struct zspage*,int) ; 
 int /*<<< orphan*/  is_zspage_isolated (struct zspage*) ; 
 int /*<<< orphan*/  set_zspage_mapping (struct zspage*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum fullness_group putback_zspage(struct size_class *class,
			struct zspage *zspage)
{
	enum fullness_group fullness;

	VM_BUG_ON(is_zspage_isolated(zspage));

	fullness = get_fullness_group(class, zspage);
	insert_zspage(class, zspage, fullness);
	set_zspage_mapping(zspage, class->index, fullness);

	return fullness;
}