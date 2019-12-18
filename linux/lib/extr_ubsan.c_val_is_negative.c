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
struct type_descriptor {int dummy; } ;

/* Variables and functions */
 scalar_t__ get_signed_val (struct type_descriptor*,void*) ; 
 scalar_t__ type_is_signed (struct type_descriptor*) ; 

__attribute__((used)) static bool val_is_negative(struct type_descriptor *type, void *val)
{
	return type_is_signed(type) && get_signed_val(type, val) < 0;
}