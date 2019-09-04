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
typedef  char mpc_val_t ;

/* Variables and functions */
 scalar_t__ isspace (char) ; 
 size_t strlen (char*) ; 

mpc_val_t *mpcf_strtrimr(mpc_val_t *x) {
  char *s = x;
  size_t l = strlen(s);
  while (isspace(s[l-1])) {
    s[l-1] = '\0'; l--;
  }
  return s;
}