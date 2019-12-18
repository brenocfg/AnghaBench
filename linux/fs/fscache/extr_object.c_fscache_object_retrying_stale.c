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
struct fscache_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fscache_n_cache_no_space_reject ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 

void fscache_object_retrying_stale(struct fscache_object *object)
{
	fscache_stat(&fscache_n_cache_no_space_reject);
}