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
struct coeff_ram {int /*<<< orphan*/  lock; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_coeff_ram_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void coeff_ram_init(struct coeff_ram *ram)
{
	init_coeff_ram_cache(ram->cache);
	mutex_init(&ram->lock);
}