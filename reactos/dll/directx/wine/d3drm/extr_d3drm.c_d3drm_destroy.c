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
struct d3drm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct d3drm*) ; 
 int /*<<< orphan*/  heap_free (struct d3drm*) ; 

__attribute__((used)) static void d3drm_destroy(struct d3drm *d3drm)
{
    heap_free(d3drm);
    TRACE("d3drm object %p is being destroyed.\n", d3drm);
}