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
typedef  enum ra_vartype { ____Placeholder_ra_vartype } ra_vartype ;

/* Variables and functions */
#define  RA_VARTYPE_BYTE_UNORM 130 
#define  RA_VARTYPE_FLOAT 129 
#define  RA_VARTYPE_INT 128 

size_t ra_vartype_size(enum ra_vartype type)
{
    switch (type) {
    case RA_VARTYPE_INT:        return sizeof(int);
    case RA_VARTYPE_FLOAT:      return sizeof(float);
    case RA_VARTYPE_BYTE_UNORM: return 1;
    default: return 0;
    }
}