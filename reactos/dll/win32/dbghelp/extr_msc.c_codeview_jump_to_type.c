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
struct codeview_type_parse {size_t num; void const* table; int* offset; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t FIRST_DEFINABLE_TYPE ; 

__attribute__((used)) static inline const void* codeview_jump_to_type(const struct codeview_type_parse* ctp, DWORD idx)
{
    if (idx < FIRST_DEFINABLE_TYPE) return NULL;
    idx -= FIRST_DEFINABLE_TYPE;
    return (idx >= ctp->num) ? NULL : (ctp->table + ctp->offset[idx]); 
}