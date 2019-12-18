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
struct xdaliclock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xdaliclock_free (struct xdaliclock*) ; 

__attribute__((used)) static void destroy_xdaliclock(void *data)
{
    struct xdaliclock *xdc = data;

    xdaliclock_free(xdc);
}