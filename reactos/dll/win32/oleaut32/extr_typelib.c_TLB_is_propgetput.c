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
typedef  scalar_t__ INVOKEKIND ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ INVOKE_PROPERTYGET ; 
 scalar_t__ INVOKE_PROPERTYPUT ; 
 scalar_t__ INVOKE_PROPERTYPUTREF ; 

__attribute__((used)) static BOOL TLB_is_propgetput(INVOKEKIND invkind)
{
    return (invkind == INVOKE_PROPERTYGET ||
        invkind == INVOKE_PROPERTYPUT ||
        invkind == INVOKE_PROPERTYPUTREF);
}