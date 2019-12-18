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
 unsigned int WORD_SIZE ; 

__attribute__((used)) static inline unsigned int compute_word_offset(char *start, unsigned int *addr)
{
	unsigned int delta_bytes, ret;
	delta_bytes = (unsigned long)addr - (unsigned long)start;

	ret = delta_bytes/WORD_SIZE;

	return ret;
}