#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct meta_value {int dummy; } ;
struct TYPE_2__ {scalar_t__ get; } ;

/* Variables and functions */
 int /*<<< orphan*/  meta_id (struct meta_value*) ; 
 TYPE_1__* meta_ops (struct meta_value*) ; 

__attribute__((used)) static inline int meta_is_supported(struct meta_value *val)
{
	return !meta_id(val) || meta_ops(val)->get;
}