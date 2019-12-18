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
typedef  int /*<<< orphan*/  CreateOpClassItem ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_args ; 
 int /*<<< orphan*/  itemtype ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  number ; 
 int /*<<< orphan*/  order_family ; 
 int /*<<< orphan*/  storedtype ; 

__attribute__((used)) static bool
_equalCreateOpClassItem(const CreateOpClassItem *a, const CreateOpClassItem *b)
{
	COMPARE_SCALAR_FIELD(itemtype);
	COMPARE_NODE_FIELD(name);
	COMPARE_SCALAR_FIELD(number);
	COMPARE_NODE_FIELD(order_family);
	COMPARE_NODE_FIELD(class_args);
	COMPARE_NODE_FIELD(storedtype);

	return true;
}