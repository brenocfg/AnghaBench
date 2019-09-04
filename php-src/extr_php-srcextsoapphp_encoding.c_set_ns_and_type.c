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
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  TYPE_1__* encodeTypePtr ;
struct TYPE_3__ {int /*<<< orphan*/  type_str; int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_ns_and_type_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_ns_and_type(xmlNodePtr node, encodeTypePtr type)
{
	set_ns_and_type_ex(node, type->ns, type->type_str);
}