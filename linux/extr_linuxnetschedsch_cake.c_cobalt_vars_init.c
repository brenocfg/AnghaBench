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
struct cobalt_vars {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cobalt_cache_init () ; 
 int /*<<< orphan*/ * cobalt_rec_inv_sqrt_cache ; 
 int /*<<< orphan*/  memset (struct cobalt_vars*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cobalt_vars_init(struct cobalt_vars *vars)
{
	memset(vars, 0, sizeof(*vars));

	if (!cobalt_rec_inv_sqrt_cache[0]) {
		cobalt_cache_init();
		cobalt_rec_inv_sqrt_cache[0] = ~0;
	}
}