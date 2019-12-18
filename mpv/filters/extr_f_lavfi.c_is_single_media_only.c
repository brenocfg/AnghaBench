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
typedef  int /*<<< orphan*/  AVFilterPad ;

/* Variables and functions */
 int avfilter_pad_count (int /*<<< orphan*/  const*) ; 
 int avfilter_pad_get_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_single_media_only(const AVFilterPad *pads, int media_type)
{
    int count = avfilter_pad_count(pads);
    if (count != 1)
        return false;
    return avfilter_pad_get_type(pads, 0) == media_type;
}