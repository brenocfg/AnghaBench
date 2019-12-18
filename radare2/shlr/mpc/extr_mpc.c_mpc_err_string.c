#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ col; scalar_t__ row; } ;
struct TYPE_5__ {int expected_num; int /*<<< orphan*/  recieved; int /*<<< orphan*/ * expected; TYPE_1__ state; int /*<<< orphan*/  filename; int /*<<< orphan*/  failure; } ;
typedef  TYPE_2__ mpc_err_t ;

/* Variables and functions */
 char* calloc (int,int) ; 
 char* mpc_err_char_unescape (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_err_string_cat (char*,int*,int*,char*,...) ; 
 char* realloc (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

char *mpc_err_string(mpc_err_t *x) {

  int i;  
  int pos = 0; 
  int max = 1023;
  char *buffer = calloc(1, 1024);
  
  if (x->failure) {
    mpc_err_string_cat(buffer, &pos, &max,
    "%s: error: %s\n", x->filename, x->failure);
    return buffer;
  }
  
  mpc_err_string_cat(buffer, &pos, &max, 
    "%s:%i:%i: error: expected ", x->filename, x->state.row+1, x->state.col+1);
  
  if (x->expected_num == 0) { mpc_err_string_cat(buffer, &pos, &max, "ERROR: NOTHING EXPECTED"); }
  if (x->expected_num == 1) { mpc_err_string_cat(buffer, &pos, &max, "%s", x->expected[0]); }
  if (x->expected_num >= 2) {
  
    for (i = 0; i < x->expected_num-2; i++) {
      mpc_err_string_cat(buffer, &pos, &max, "%s, ", x->expected[i]);
    } 
    
    mpc_err_string_cat(buffer, &pos, &max, "%s or %s", 
      x->expected[x->expected_num-2], 
      x->expected[x->expected_num-1]);
  }
  
  mpc_err_string_cat(buffer, &pos, &max, " at ");
  mpc_err_string_cat(buffer, &pos, &max, mpc_err_char_unescape(x->recieved));
  mpc_err_string_cat(buffer, &pos, &max, "\n");
  
  return realloc(buffer, strlen(buffer) + 1);
}