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
 unsigned long LOW_MEMORY ; 
 int PAGE_SIZE ; 
 int PAGING_PAGES ; 
 int* mem_map ; 

unsigned long get_free_page() {
  for (int i = 0; i < PAGING_PAGES; i++) {
    if (mem_map[i] == 0) {
      mem_map[i] = 1;
      return LOW_MEMORY + i * PAGE_SIZE;
    }
  }
  return 0;
}