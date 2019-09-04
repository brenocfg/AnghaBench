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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

int memcmp(const void * ptr1, const void * ptr2, unsigned int num) {
  int i;
  for (i = 0; i < num; i++) {
    if ( ((uint8_t*)ptr1)[i] != ((uint8_t*)ptr2)[i] ) return -1;
  }
  return 0;
}