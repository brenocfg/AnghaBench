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
typedef  int /*<<< orphan*/  v ;
struct cobalt_vars {unsigned int rec_inv_sqrt; int count; } ;

/* Variables and functions */
 int REC_INV_SQRT_CACHE ; 
 int /*<<< orphan*/  cobalt_newton_step (struct cobalt_vars*) ; 
 unsigned int* cobalt_rec_inv_sqrt_cache ; 
 int /*<<< orphan*/  memset (struct cobalt_vars*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cobalt_cache_init(void)
{
	struct cobalt_vars v;

	memset(&v, 0, sizeof(v));
	v.rec_inv_sqrt = ~0U;
	cobalt_rec_inv_sqrt_cache[0] = v.rec_inv_sqrt;

	for (v.count = 1; v.count < REC_INV_SQRT_CACHE; v.count++) {
		cobalt_newton_step(&v);
		cobalt_newton_step(&v);
		cobalt_newton_step(&v);
		cobalt_newton_step(&v);

		cobalt_rec_inv_sqrt_cache[v.count] = v.rec_inv_sqrt;
	}
}