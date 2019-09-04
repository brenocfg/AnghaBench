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
struct TYPE_3__ {char recieved; void* failure; int /*<<< orphan*/ * expected; scalar_t__ expected_num; int /*<<< orphan*/  state; void* filename; } ;
typedef  TYPE_1__ mpc_err_t ;

/* Variables and functions */
 void* malloc (int) ; 
 int /*<<< orphan*/  mpc_state_new () ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static mpc_err_t *mpc_err_file(const char *filename, const char *failure) {
  mpc_err_t *x;
  x = malloc(sizeof(mpc_err_t));
  x->filename = malloc(strlen(filename) + 1);
  strcpy(x->filename, filename);
  x->state = mpc_state_new();
  x->expected_num = 0;
  x->expected = NULL;
  x->failure = malloc(strlen(failure) + 1);
  strcpy(x->failure, failure);
  x->recieved = ' ';
  return x;
}