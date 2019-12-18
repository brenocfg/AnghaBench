#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_input_t ;
struct TYPE_9__ {scalar_t__ pos; } ;
struct TYPE_8__ {int expected_num; int /*<<< orphan*/ * expected; int /*<<< orphan*/  recieved; int /*<<< orphan*/ * failure; TYPE_2__ state; int /*<<< orphan*/ * filename; } ;
typedef  TYPE_1__ mpc_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_err_add_expected (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_err_contains_expected (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_err_delete_internal (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* mpc_malloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ mpc_state_invalid () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mpc_err_t *mpc_err_or(mpc_input_t *i, mpc_err_t** x, int n) {
  
  int j, k, fst;
  mpc_err_t *e;
  
  fst = -1;
  for (j = 0; j < n; j++) {
    if (x[j] != NULL) { fst = j; }
  }
  
  if (fst == -1) { return NULL; }
  
  e = mpc_malloc(i, sizeof(mpc_err_t));
  e->state = mpc_state_invalid();
  e->expected_num = 0;
  e->expected = NULL;
  e->failure = NULL;
  e->filename = mpc_malloc(i, strlen(x[fst]->filename)+1);
  strcpy(e->filename, x[fst]->filename);
  
  for (j = 0; j < n; j++) {
    if (!x[j]) { continue; }
    if (x[j]->state.pos > e->state.pos) { e->state = x[j]->state; }
  }
  
  for (j = 0; j < n; j++) {
    if (!x[j]) { continue; }
    if (x[j]->state.pos < e->state.pos) { continue; }
    
    if (x[j]->failure) {
      e->failure = mpc_malloc(i, strlen(x[j]->failure)+1);
      strcpy(e->failure, x[j]->failure);
      break;
    }
    
    e->recieved = x[j]->recieved;
    
    for (k = 0; k < x[j]->expected_num; k++) {
      if (!mpc_err_contains_expected(i, e, x[j]->expected[k])) {
        mpc_err_add_expected(i, e, x[j]->expected[k]);
      }
    }
  }
  
  for (j = 0; j < n; j++) {
    if (!x[j]) { continue; }
    mpc_err_delete_internal(i, x[j]);
  }
  
  return e;
}