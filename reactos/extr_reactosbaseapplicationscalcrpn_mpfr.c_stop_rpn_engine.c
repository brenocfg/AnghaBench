#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mf; } ;
struct TYPE_11__ {TYPE_3__ number; } ;
struct TYPE_9__ {int /*<<< orphan*/  mf; } ;
struct TYPE_8__ {int /*<<< orphan*/  mf; } ;
struct TYPE_14__ {TYPE_4__ memory; TYPE_2__ prev; TYPE_1__ code; } ;
struct TYPE_12__ {int /*<<< orphan*/  mf; } ;
struct TYPE_13__ {TYPE_5__ number; } ;

/* Variables and functions */
 TYPE_7__ calc ; 
 int /*<<< orphan*/  mpfr_clear (int /*<<< orphan*/ ) ; 
 TYPE_6__ temp ; 

void stop_rpn_engine(void)
{
    mpfr_clear(calc.code.mf);
    mpfr_clear(calc.prev.mf);
    mpfr_clear(calc.memory.number.mf);
    mpfr_clear(temp.number.mf);
}