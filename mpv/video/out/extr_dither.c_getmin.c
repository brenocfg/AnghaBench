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
typedef  scalar_t__ uint64_t ;
struct ctx {unsigned int size2; scalar_t__* gaussmat; unsigned int* randomat; int /*<<< orphan*/  avlfg; scalar_t__* calcmat; } ;
typedef  unsigned int index_t ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 
 unsigned int av_lfg_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static index_t getmin(struct ctx *k)
{
    uint64_t min = UINT64_MAX;
    index_t resnum = 0;
    unsigned int size2 = k->size2;
    for (index_t c = 0; c < size2; c++) {
        if (k->calcmat[c])
            continue;
        uint64_t total = k->gaussmat[c];
        if (total <= min) {
            if (total != min) {
                min = total;
                resnum = 0;
            }
            k->randomat[resnum++] = c;
        }
    }
    if (resnum == 1)
        return k->randomat[0];
    if (resnum == size2)
        return size2 / 2;
    return k->randomat[av_lfg_get(&k->avlfg) % resnum];
}