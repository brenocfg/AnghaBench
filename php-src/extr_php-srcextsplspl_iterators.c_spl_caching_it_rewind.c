#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zcache; } ;
struct TYPE_8__ {TYPE_1__ caching; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
typedef  TYPE_3__ spl_dual_it_object ;

/* Variables and functions */
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_caching_it_next (TYPE_3__*) ; 
 int /*<<< orphan*/  spl_dual_it_rewind (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_hash_clean (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void spl_caching_it_rewind(spl_dual_it_object *intern)
{
	spl_dual_it_rewind(intern);
	zend_hash_clean(Z_ARRVAL(intern->u.caching.zcache));
	spl_caching_it_next(intern);
}