#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpca_count (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpca_many (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpca_many1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpca_maybe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpca_not (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mpc_val_t *mpcaf_grammar_repeat(int n, mpc_val_t **xs) { 
  int num;
  (void) n;
  if (!xs[1]) { return xs[0]; }  
  if (strcmp(xs[1], "*") == 0) { free(xs[1]); return mpca_many(xs[0]); }
  if (strcmp(xs[1], "+") == 0) { free(xs[1]); return mpca_many1(xs[0]); }
  if (strcmp(xs[1], "?") == 0) { free(xs[1]); return mpca_maybe(xs[0]); }
  if (strcmp(xs[1], "!") == 0) { free(xs[1]); return mpca_not(xs[0]); }
  num = *((int*)xs[1]);
  free(xs[1]);
  return mpca_count(num, xs[0]);
}