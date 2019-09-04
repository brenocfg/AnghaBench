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
struct TYPE_4__ {char const* tag; } ;
typedef  TYPE_1__ mpc_ast_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char const*,char const*,int) ; 
 char const* realloc (char const*,int) ; 
 int strlen (char const*) ; 

mpc_ast_t *mpc_ast_add_tag(mpc_ast_t *a, const char *t) {
  if (!a) { return a; }
  a->tag = realloc(a->tag, strlen(t) + 1 + strlen(a->tag) + 1);
  memmove(a->tag + strlen(t) + 1, a->tag, strlen(a->tag)+1);
  memmove(a->tag, t, strlen(t));
  memmove(a->tag + strlen(t), "|", 1);
  return a;
}