#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ caching; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ spl_dual_it_object ;

/* Variables and functions */
 int CIT_VALID ; 
 int FAILURE ; 
 int SUCCESS ; 

__attribute__((used)) static inline int spl_caching_it_valid(spl_dual_it_object *intern)
{
	return intern->u.caching.flags & CIT_VALID ? SUCCESS : FAILURE;
}