#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ao {scalar_t__ format; } ;
struct TYPE_5__ {int /*<<< orphan*/  SubFormat; } ;
typedef  TYPE_1__ WAVEFORMATEXTENSIBLE ;

/* Variables and functions */
 scalar_t__ AF_FORMAT_S_AC3 ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*) ; 
 scalar_t__ af_fmt_is_spdif (scalar_t__) ; 
 int /*<<< orphan*/ * format_to_subtype (scalar_t__) ; 
 int search_channels (struct ao*,TYPE_1__*) ; 
 scalar_t__ try_format_exclusive (struct ao*,TYPE_1__*) ; 

__attribute__((used)) static bool find_formats_exclusive(struct ao *ao, WAVEFORMATEXTENSIBLE *wformat)
{
    // Try the specified format as is
    if (try_format_exclusive(ao, wformat))
        return true;

    if (af_fmt_is_spdif(ao->format)) {
        if (ao->format != AF_FORMAT_S_AC3) {
            // If the requested format failed and it is passthrough, but not
            // AC3, try lying and saying it is.
            MP_VERBOSE(ao, "Retrying as AC3.\n");
            wformat->SubFormat = *format_to_subtype(AF_FORMAT_S_AC3);
            if (try_format_exclusive(ao, wformat))
                return true;
        }
        return false;
    }

    // Fallback on the PCM format search
    return search_channels(ao, wformat);
}