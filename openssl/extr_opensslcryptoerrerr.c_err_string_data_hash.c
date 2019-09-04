#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long error; } ;
typedef  TYPE_1__ ERR_STRING_DATA ;

/* Variables and functions */
 unsigned long ERR_GET_FUNC (unsigned long) ; 
 unsigned long ERR_GET_LIB (unsigned long) ; 

__attribute__((used)) static unsigned long err_string_data_hash(const ERR_STRING_DATA *a)
{
    unsigned long ret, l;

    l = a->error;
    ret = l ^ ERR_GET_LIB(l) ^ ERR_GET_FUNC(l);
    return (ret ^ ret % 19 * 13);
}