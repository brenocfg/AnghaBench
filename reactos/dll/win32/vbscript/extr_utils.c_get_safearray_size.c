#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
typedef  int ULONG ;
struct TYPE_5__ {size_t cDims; TYPE_1__* rgsabound; } ;
struct TYPE_4__ {int cElements; } ;
typedef  TYPE_2__ SAFEARRAY ;

/* Variables and functions */

__attribute__((used)) static ULONG get_safearray_size(SAFEARRAY *sa)
{
    ULONG ret = 1;
    USHORT i;

    if(!sa)
        return 0;

    for(i=0; i<sa->cDims && ret; i++)
        ret *= sa->rgsabound[i].cElements;
    return ret;
}