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
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  int /*<<< orphan*/  JsonPathGinNode ;

/* Variables and functions */
 int /*<<< orphan*/ * make_jsp_entry_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_scalar_key (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static JsonPathGinNode *
make_jsp_entry_node_scalar(JsonbValue *scalar, bool iskey)
{
	return make_jsp_entry_node(make_scalar_key(scalar, iskey));
}