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
struct ra {int dummy; } ;
struct d3d_timer {int /*<<< orphan*/  disjoint; int /*<<< orphan*/  ts_end; int /*<<< orphan*/  ts_start; } ;
typedef  struct d3d_timer ra_timer ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct d3d_timer*) ; 

__attribute__((used)) static void timer_destroy(struct ra *ra, ra_timer *ratimer)
{
    if (!ratimer)
        return;
    struct d3d_timer *timer = ratimer;

    SAFE_RELEASE(timer->ts_start);
    SAFE_RELEASE(timer->ts_end);
    SAFE_RELEASE(timer->disjoint);
    talloc_free(timer);
}