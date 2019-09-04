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

void
hash_debug_results()
{
#ifdef HT_DEBUG
    fprintf(stderr, "\r\n\r\n\r\n\r\n");
    fprintf(stderr, "Number of hashtable lookups: %ld\r\n", hash_count_lookup);
    fprintf(stderr, "Number of perturb loops: %ld\r\n", hash_count_perturb);
    fprintf(stderr, "Percentage of perturb loops: %ld%%\r\n",
				hash_count_perturb * 100 / hash_count_lookup);
#endif
}