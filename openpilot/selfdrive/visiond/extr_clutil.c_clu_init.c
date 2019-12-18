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
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void clu_init(void) {
#ifndef CLU_NO_SRC
  mkdir("/tmp/clcache", 0777);
  unlink("/tmp/clcache/index.cli");
#endif
}