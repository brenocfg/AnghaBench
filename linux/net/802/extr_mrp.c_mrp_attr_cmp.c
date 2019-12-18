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
typedef  scalar_t__ u8 ;
struct mrp_attr {scalar_t__ type; scalar_t__ len; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

__attribute__((used)) static int mrp_attr_cmp(const struct mrp_attr *attr,
			 const void *value, u8 len, u8 type)
{
	if (attr->type != type)
		return attr->type - type;
	if (attr->len != len)
		return attr->len - len;
	return memcmp(attr->value, value, len);
}