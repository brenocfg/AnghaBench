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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_rtmp_create_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_send_shared_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_rtmp_send_abort(ngx_rtmp_session_t *s, uint32_t csid)
{
    return ngx_rtmp_send_shared_packet(s,
           ngx_rtmp_create_abort(s, csid));
}