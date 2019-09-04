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
struct TYPE_3__ {int /*<<< orphan*/ * rrec; } ;
typedef  TYPE_1__ RECORD_LAYER ;

/* Variables and functions */
 size_t SSL3_RECORD_get_length (int /*<<< orphan*/ *) ; 

size_t RECORD_LAYER_get_rrec_length(RECORD_LAYER *rl)
{
    return SSL3_RECORD_get_length(&rl->rrec[0]);
}