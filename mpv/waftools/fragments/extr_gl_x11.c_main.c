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
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  glXCreateContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXGetCurrentDisplay () ; 
 int /*<<< orphan*/  glXGetProcAddressARB (char*) ; 
 int /*<<< orphan*/  glXQueryExtensionsString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
  glXCreateContext(NULL, NULL, NULL, True);
  glXQueryExtensionsString(NULL, 0);
  glXGetProcAddressARB("");
  glXGetCurrentDisplay();
  return 0;
}