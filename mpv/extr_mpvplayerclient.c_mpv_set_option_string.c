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
typedef  int /*<<< orphan*/  mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_STRING ; 
 int mpv_set_option (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const**) ; 

int mpv_set_option_string(mpv_handle *ctx, const char *name, const char *data)
{
    return mpv_set_option(ctx, name, MPV_FORMAT_STRING, &data);
}