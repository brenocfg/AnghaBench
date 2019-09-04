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
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ fnditem ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void add_fi (fnditem* n, unsigned char* blk, int patlen) {
	fnditem* p;
	for (p = n; p->next != NULL; p = p->next) {
		;
	}
	p->next = (fnditem*) malloc (sizeof (fnditem));
	p = p->next;
	memcpy (p->str, blk, patlen);
	p->next = NULL;
}