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
struct TYPE_3__ {int /*<<< orphan*/  str; struct TYPE_3__* next; } ;
typedef  TYPE_1__ fnditem ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int is_fi_present(fnditem* n, unsigned char* blk , int patlen) {
	fnditem* p;
	for (p = n; p->next != NULL; p = p->next) {
		if (!memcmp (blk, p->str, patlen)) {
			return true;
		}
	}
	return false;
}