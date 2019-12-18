#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  HCCtx; int /*<<< orphan*/  fastCtx; struct TYPE_4__* dictContent; } ;
typedef  TYPE_1__ LZ4F_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  FREEMEM (TYPE_1__*) ; 
 int /*<<< orphan*/  LZ4_freeStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4_freeStreamHC (int /*<<< orphan*/ ) ; 

void LZ4F_freeCDict(LZ4F_CDict* cdict)
{
    if (cdict==NULL) return;  /* support free on NULL */
    FREEMEM(cdict->dictContent);
    LZ4_freeStream(cdict->fastCtx);
    LZ4_freeStreamHC(cdict->HCCtx);
    FREEMEM(cdict);
}