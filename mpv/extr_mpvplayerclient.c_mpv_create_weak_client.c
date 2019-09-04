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
 int /*<<< orphan*/  mp_client_set_weak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpv_create_client (int /*<<< orphan*/ *,char const*) ; 

mpv_handle *mpv_create_weak_client(mpv_handle *ctx, const char *name)
{
    mpv_handle *new = mpv_create_client(ctx, name);
    if (new)
        mp_client_set_weak(new);
    return new;
}