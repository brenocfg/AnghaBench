#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  x; } ;
struct TYPE_9__ {TYPE_1__ string; } ;
struct TYPE_10__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_STRING ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 TYPE_3__* mpc_expectf (TYPE_3__*,char*,char const*) ; 
 TYPE_3__* mpc_undefined () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

mpc_parser_t *mpc_string(const char *s) {
  mpc_parser_t *p = mpc_undefined();
  p->type = MPC_TYPE_STRING;
  p->data.string.x = malloc(strlen(s) + 1);
  strcpy(p->data.string.x, s);
  return mpc_expectf(p, "\"%s\"", s);
}