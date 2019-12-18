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
typedef  int /*<<< orphan*/  mpc_input_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_input_char (int /*<<< orphan*/ *,char const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_input_mark (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_input_rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_input_unmark (int /*<<< orphan*/ *) ; 
 char* mpc_malloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int mpc_input_string(mpc_input_t *i, const char *c, char **o) {
  
  const char *x = c;

  mpc_input_mark(i);
  while (*x) {
    if (!mpc_input_char(i, *x, NULL)) {
      mpc_input_rewind(i);
      return 0;
    }
    x++;
  }
  mpc_input_unmark(i);
  
  *o = mpc_malloc(i, strlen(c) + 1);
  strcpy(*o, c);
  return 1;
}