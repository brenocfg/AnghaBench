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
struct TYPE_3__ {int /*<<< orphan*/ * children; scalar_t__ children_num; int /*<<< orphan*/  state; void* contents; void* tag; } ;
typedef  TYPE_1__ mpc_ast_t ;

/* Variables and functions */
 void* malloc (int) ; 
 int /*<<< orphan*/  mpc_state_new () ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 int strlen (char const*) ; 

mpc_ast_t *mpc_ast_new(const char *tag, const char *contents) {
  
  mpc_ast_t *a = malloc(sizeof(mpc_ast_t));
  
  a->tag = malloc(strlen(tag) + 1);
  strcpy(a->tag, tag);
  
  a->contents = malloc(strlen(contents) + 1);
  strcpy(a->contents, contents);
  
  a->state = mpc_state_new();
  
  a->children_num = 0;
  a->children = NULL;
  return a;
  
}