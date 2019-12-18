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
typedef  int /*<<< orphan*/  litDistribTable ;

/* Variables and functions */
 int /*<<< orphan*/  RDG_fillLiteralDistrib (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  RDG_genBlock (void*,size_t,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,unsigned int*) ; 

void RDG_genBuffer(void* buffer, size_t size, double matchProba, double litProba, unsigned seed)
{
    litDistribTable lt;
    if (litProba==0.0) litProba = matchProba / 4.5;
    RDG_fillLiteralDistrib(lt, litProba);
    RDG_genBlock(buffer, size, 0, matchProba, lt, &seed);
}