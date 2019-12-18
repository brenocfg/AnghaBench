#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ref; } ;
struct TYPE_5__ {TYPE_2__ type; } ;
typedef  TYPE_2__ CType ;

/* Variables and functions */

__attribute__((used)) static inline CType *pointed_type(CType *type) {
	return &type->ref->type;
}