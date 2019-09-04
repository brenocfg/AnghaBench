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
struct hlsl_type {scalar_t__ type; } ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ HLSL_CLASS_OBJECT ; 

__attribute__((used)) static BOOL convertible_data_type(struct hlsl_type *type)
{
    return type->type != HLSL_CLASS_OBJECT;
}