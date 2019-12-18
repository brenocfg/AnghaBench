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
struct TYPE_3__ {unsigned int rate; scalar_t__ squeezing; scalar_t__ byteIOIndex; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SpongeInstance ;

/* Variables and functions */
 int /*<<< orphan*/  SnP_Initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnP_StaticInitialize () ; 
 unsigned int SnP_width ; 

int SpongeInitialize(SpongeInstance *instance, unsigned int rate, unsigned int capacity)
{
    if (rate+capacity != SnP_width)
        return 1;
    if ((rate <= 0) || (rate > SnP_width) || ((rate % 8) != 0))
        return 1;
    SnP_StaticInitialize();
    SnP_Initialize(instance->state);
    instance->rate = rate;
    instance->byteIOIndex = 0;
    instance->squeezing = 0;

    return 0;
}