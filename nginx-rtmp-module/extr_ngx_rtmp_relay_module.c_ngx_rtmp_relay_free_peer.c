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
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_peer_connection_t ;

/* Variables and functions */

__attribute__((used)) static void
ngx_rtmp_relay_free_peer(ngx_peer_connection_t *pc, void *data,
            ngx_uint_t state)
{
}