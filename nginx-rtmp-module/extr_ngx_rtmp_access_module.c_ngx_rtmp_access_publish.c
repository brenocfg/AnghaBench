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
struct TYPE_5__ {scalar_t__ auto_pushed; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_publish_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_ACCESS_PUBLISH ; 
 int /*<<< orphan*/  next_publish (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_rtmp_access (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_access_publish(ngx_rtmp_session_t *s, ngx_rtmp_publish_t *v)
{
    if (s->auto_pushed) {
        goto next;
    }

    if (ngx_rtmp_access(s, NGX_RTMP_ACCESS_PUBLISH) != NGX_OK) {
        return NGX_ERROR;
    }

next:
    return next_publish(s, v);
}