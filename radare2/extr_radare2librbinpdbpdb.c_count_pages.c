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

__attribute__((used)) static int count_pages(int length, int page_size) {
	int num_pages = 0;
	if (page_size > 0) {
		num_pages = length / page_size;
		if (length % page_size) {
			num_pages++;
		}
	}
	return num_pages;
}