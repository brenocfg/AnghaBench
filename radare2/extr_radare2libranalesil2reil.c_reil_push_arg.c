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
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RAnalReilArg ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_anal_esil_push (int /*<<< orphan*/ *,char*) ; 
 char* r_str_newf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void reil_push_arg(RAnalEsil *esil, RAnalReilArg *op) {
	char *s = r_str_newf ("%s:%d", op->name, op->size);
	r_anal_esil_push (esil, s);
	free (s);
}