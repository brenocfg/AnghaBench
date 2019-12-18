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
struct _headerInfo {int _value; } ;

/* Variables and functions */

int compareValueLocation(const void * v1, const void *v2 )
{
    return ((const struct _headerInfo *)v1)->_value -
           ((const struct _headerInfo *)v2)->_value;
}