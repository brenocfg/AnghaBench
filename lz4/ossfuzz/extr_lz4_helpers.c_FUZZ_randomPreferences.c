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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {void* favorDecSpeed; void* autoFlush; scalar_t__ compressionLevel; int /*<<< orphan*/  frameInfo; } ;
typedef  TYPE_1__ LZ4F_preferences_t ;

/* Variables and functions */
 void* FUZZ_rand32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FUZZ_randomFrameInfo (int /*<<< orphan*/ *) ; 
 TYPE_1__ LZ4F_INIT_PREFERENCES ; 
 int LZ4HC_CLEVEL_MAX ; 

LZ4F_preferences_t FUZZ_randomPreferences(uint32_t* seed)
{
    LZ4F_preferences_t prefs = LZ4F_INIT_PREFERENCES;
    prefs.frameInfo = FUZZ_randomFrameInfo(seed);
    prefs.compressionLevel = FUZZ_rand32(seed, 0, LZ4HC_CLEVEL_MAX + 3) - 3;
    prefs.autoFlush = FUZZ_rand32(seed, 0, 1);
    prefs.favorDecSpeed = FUZZ_rand32(seed, 0, 1);
    return prefs;
}