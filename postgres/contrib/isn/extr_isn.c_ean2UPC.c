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
 int /*<<< orphan*/  dehyphenate (char*,char*) ; 

__attribute__((used)) static inline void
ean2UPC(char *isn)
{
	/* the number should come in this format: 000-000000000-0 */
	/* Strip the first part, crop, and dehyphenate */
	dehyphenate(isn, isn + 1);
	isn[12] = '\0';
}