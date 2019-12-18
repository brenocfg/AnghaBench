#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int retained; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ mpc_parser_t ;

/* Variables and functions */
 TYPE_1__* mpc_undefined () ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

mpc_parser_t *mpc_new(const char *name) {
  mpc_parser_t *p = mpc_undefined();
  p->retained = 1;
  p->name = realloc(p->name, strlen(name) + 1);
  strcpy(p->name, name);
  return p;
}