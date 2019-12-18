#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ RPVector ;

/* Variables and functions */
 scalar_t__ r_vector_insert (int /*<<< orphan*/ *,size_t,void**) ; 

__attribute__((used)) static inline void **r_pvector_insert(RPVector *vec, size_t index, void *x) {
	return (void **)r_vector_insert (&vec->v, index, &x);
}