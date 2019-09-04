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
struct TYPE_3__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ fnditem ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

__attribute__((used)) static fnditem* init_fi() {
	fnditem* n;
	n = (fnditem*) malloc (sizeof (fnditem));
	if (!n) {
		return NULL;
	}
	n->next = NULL;
	return n;
}