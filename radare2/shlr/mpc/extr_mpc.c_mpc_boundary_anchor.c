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

/* Variables and functions */
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static int mpc_boundary_anchor(char prev, char next) {
  const char* word = "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "0123456789_";
  if ( strchr(word, next) &&  prev == '\0') { return 1; }
  if ( strchr(word, prev) &&  next == '\0') { return 1; }
  if ( strchr(word, next) && !strchr(word, prev)) { return 1; }
  if (!strchr(word, next) &&  strchr(word, prev)) { return 1; }
  return 0;
}