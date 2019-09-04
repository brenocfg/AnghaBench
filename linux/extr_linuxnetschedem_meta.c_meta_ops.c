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
struct meta_value {int dummy; } ;
struct meta_ops {int dummy; } ;

/* Variables and functions */
 struct meta_ops** __meta_ops ; 
 size_t meta_id (struct meta_value*) ; 
 size_t meta_type (struct meta_value*) ; 

__attribute__((used)) static inline struct meta_ops *meta_ops(struct meta_value *val)
{
	return &__meta_ops[meta_type(val)][meta_id(val)];
}