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
struct frequency_limit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct frequency_limit*) ; 

void
frequency_limit_free(struct frequency_limit *f)
{
    free(f);
}