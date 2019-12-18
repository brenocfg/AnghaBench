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
typedef  int /*<<< orphan*/  uint64_t ;
struct ctx {int* calcmat; int size2; int gauss_middle; int /*<<< orphan*/ * gauss; int /*<<< orphan*/ * gaussmat; } ;
typedef  size_t index_t ;

/* Variables and functions */
 int WRAP_SIZE2 (struct ctx*,int) ; 

__attribute__((used)) static void setbit(struct ctx *k, index_t c)
{
    if (k->calcmat[c])
        return;
    k->calcmat[c] = true;
    uint64_t *m = k->gaussmat;
    uint64_t *me = k->gaussmat + k->size2;
    uint64_t *g = k->gauss + WRAP_SIZE2(k, k->gauss_middle + k->size2 - c);
    uint64_t *ge = k->gauss + k->size2;
    while (g < ge)
        *m++ += *g++;
    g = k->gauss;
    while (m < me)
        *m++ += *g++;
}