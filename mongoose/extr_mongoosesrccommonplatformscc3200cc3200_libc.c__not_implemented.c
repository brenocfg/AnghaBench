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
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  fprint_str (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stderr ; 

void _not_implemented(const char *what) {
  fprint_str(stderr, what);
  fprint_str(stderr, " is not implemented\n");
  _exit(42);
}