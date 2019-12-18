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
struct mpv_global {int dummy; } ;
struct mp_ipc_ctx {int dummy; } ;
struct mp_client_api {int dummy; } ;

/* Variables and functions */

struct mp_ipc_ctx *mp_init_ipc(struct mp_client_api *client_api,
                               struct mpv_global *global)
{
    return NULL;
}