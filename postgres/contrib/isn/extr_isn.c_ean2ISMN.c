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
 int /*<<< orphan*/  hyphenate (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ean2ISMN(char *isn)
{
	/* the number should come in this format: 979-0-000-00000-0 */
	/* Just strip the first part and change the first digit ('0') to 'M' */
	hyphenate(isn, isn + 4, NULL, NULL);
	isn[0] = 'M';
}