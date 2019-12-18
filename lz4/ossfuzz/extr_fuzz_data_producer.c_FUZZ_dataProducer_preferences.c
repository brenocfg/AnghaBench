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
struct TYPE_4__ {void* favorDecSpeed; void* autoFlush; scalar_t__ compressionLevel; int /*<<< orphan*/  frameInfo; } ;
typedef  TYPE_1__ LZ4F_preferences_t ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_dataProducer_frameInfo (int /*<<< orphan*/ *) ; 
 void* FUZZ_dataProducer_range32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ LZ4F_INIT_PREFERENCES ; 
 int LZ4HC_CLEVEL_MAX ; 

LZ4F_preferences_t FUZZ_dataProducer_preferences(FUZZ_dataProducer_t* producer)
{
    LZ4F_preferences_t prefs = LZ4F_INIT_PREFERENCES;
    prefs.frameInfo = FUZZ_dataProducer_frameInfo(producer);
    prefs.compressionLevel = FUZZ_dataProducer_range32(producer, 0, LZ4HC_CLEVEL_MAX + 3) - 3;
    prefs.autoFlush = FUZZ_dataProducer_range32(producer, 0, 1);
    prefs.favorDecSpeed = FUZZ_dataProducer_range32(producer, 0, 1);
    return prefs;
}