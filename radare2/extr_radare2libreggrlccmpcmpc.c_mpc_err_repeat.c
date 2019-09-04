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
typedef  int /*<<< orphan*/  mpc_input_t ;
struct TYPE_4__ {int expected_num; char** expected; } ;
typedef  TYPE_1__ mpc_err_t ;

/* Variables and functions */
 char* mpc_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mpc_free (int /*<<< orphan*/ *,char*) ; 
 char* mpc_malloc (int /*<<< orphan*/ *,size_t) ; 
 void* mpc_realloc (int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static mpc_err_t *mpc_err_repeat(mpc_input_t *i, mpc_err_t *x, const char *prefix) {

  int j = 0;
  size_t l = 0;
  char *expect = NULL;
  
  if (!x) { return NULL; }
  
  if (x->expected_num == 0) {
    expect = mpc_calloc(i, 1, 1);
    x->expected_num = 1;
    x->expected = mpc_realloc(i, x->expected, sizeof(char*) * x->expected_num);
    x->expected[0] = expect;
    return x;
  }
  
  else if (x->expected_num == 1) {
    expect = mpc_malloc(i, strlen(prefix) + strlen(x->expected[0]) + 1);
    strcpy(expect, prefix);
    strcat(expect, x->expected[0]);
    mpc_free(i, x->expected[0]);
    x->expected[0] = expect;
    return x;
  }
  
  else if (x->expected_num > 1) {
    
    l += strlen(prefix);
    for (j = 0; j < x->expected_num-2; j++) {
      l += strlen(x->expected[j]) + strlen(", ");
    }
    l += strlen(x->expected[x->expected_num-2]);
    l += strlen(" or ");
    l += strlen(x->expected[x->expected_num-1]);
    
    expect = mpc_malloc(i, l + 1);
    
    strcpy(expect, prefix);
    for (j = 0; j < x->expected_num-2; j++) {
      strcat(expect, x->expected[j]); strcat(expect, ", ");
    }
    strcat(expect, x->expected[x->expected_num-2]);
    strcat(expect, " or ");
    strcat(expect, x->expected[x->expected_num-1]);

    for (j = 0; j < x->expected_num; j++) { mpc_free(i, x->expected[j]); }
    
    x->expected_num = 1;
    x->expected = mpc_realloc(i, x->expected, sizeof(char*) * x->expected_num);
    x->expected[0] = expect;
    return x;
  }
  
  return NULL;
}