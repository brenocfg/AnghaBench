#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {scalar_t__ Denominator; scalar_t__ Numerator; } ;
struct TYPE_7__ {size_t modeInfoIdx; TYPE_3__ refreshRate; } ;
struct TYPE_8__ {TYPE_1__ targetInfo; } ;
typedef  TYPE_2__ DISPLAYCONFIG_PATH_INFO ;
typedef  int /*<<< orphan*/  DISPLAYCONFIG_MODE_INFO ;

/* Variables and functions */
 size_t DISPLAYCONFIG_PATH_MODE_IDX_INVALID ; 
 int /*<<< orphan*/  displayconfig_load ; 
 int /*<<< orphan*/  displayconfig_load_ran ; 
 int /*<<< orphan*/  displayconfig_loaded ; 
 scalar_t__ get_config (void*,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_2__* get_path (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/  const*) ; 
 double get_refresh_rate_from_mode (int /*<<< orphan*/ *) ; 
 scalar_t__ is_valid_refresh_rate (TYPE_3__) ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

double mp_w32_displayconfig_get_refresh_rate(const wchar_t *device)
{
    // Load Windows 7 DisplayConfig API
    pthread_once(&displayconfig_load_ran, displayconfig_load);
    if (!displayconfig_loaded)
        return 0.0;

    void *ctx = talloc_new(NULL);
    double freq = 0.0;

    // Get the current display configuration
    UINT32 num_paths;
    DISPLAYCONFIG_PATH_INFO* paths;
    UINT32 num_modes;
    DISPLAYCONFIG_MODE_INFO* modes;
    if (get_config(ctx, &num_paths, &paths, &num_modes, &modes))
        goto end;

    // Get the path for the specified monitor
    DISPLAYCONFIG_PATH_INFO* path;
    if (!(path = get_path(num_paths, paths, device)))
        goto end;

    // Try getting the refresh rate from the mode first. The value in the mode
    // overrides the value in the path.
    if (path->targetInfo.modeInfoIdx != DISPLAYCONFIG_PATH_MODE_IDX_INVALID)
        freq = get_refresh_rate_from_mode(&modes[path->targetInfo.modeInfoIdx]);

    // If the mode didn't contain a valid refresh rate, try the path
    if (freq == 0.0 && is_valid_refresh_rate(path->targetInfo.refreshRate)) {
        freq = ((double)path->targetInfo.refreshRate.Numerator) /
               ((double)path->targetInfo.refreshRate.Denominator);
    }

end:
    talloc_free(ctx);
    return freq;
}