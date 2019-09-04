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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  CType ;

/* Variables and functions */
 int nocode_wanted ; 
 int /*<<< orphan*/  unary () ; 
 TYPE_1__* vtop ; 

__attribute__((used)) static void unary_type(CType *type) {
	int a = nocode_wanted;
	nocode_wanted = 1;
	unary ();
	*type = vtop->type;
	nocode_wanted = a;
}