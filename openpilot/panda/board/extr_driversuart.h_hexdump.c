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
 int /*<<< orphan*/  puth2 (unsigned char const) ; 
 int /*<<< orphan*/  puts (char*) ; 

void hexdump(const void *a, int l) {
  if (a != NULL) {
    for (int i=0; i < l; i++) {
      if ((i != 0) && ((i & 0xf) == 0)) puts("\n");
      puth2(((const unsigned char*)a)[i]);
      puts(" ");
    }
  }
  puts("\n");
}