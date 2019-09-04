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
struct garp_attr {scalar_t__ type; scalar_t__ dlen; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

__attribute__((used)) static int garp_attr_cmp(const struct garp_attr *attr,
			 const void *data, u8 len, u8 type)
{
	if (attr->type != type)
		return attr->type - type;
	if (attr->dlen != len)
		return attr->dlen - len;
	return memcmp(attr->data, data, len);
}