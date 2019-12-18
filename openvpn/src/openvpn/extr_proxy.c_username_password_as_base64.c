#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  password; int /*<<< orphan*/  username; } ;
struct http_proxy_info {TYPE_1__ up; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BSTR (struct buffer*) ; 
 struct buffer alloc_buf_gc (scalar_t__,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ make_base64_string (int /*<<< orphan*/  const*,struct gc_arena*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
username_password_as_base64(const struct http_proxy_info *p,
                            struct gc_arena *gc)
{
    struct buffer out = alloc_buf_gc(strlen(p->up.username) + strlen(p->up.password) + 2, gc);
    ASSERT(strlen(p->up.username) > 0);
    buf_printf(&out, "%s:%s", p->up.username, p->up.password);
    return (const char *)make_base64_string((const uint8_t *)BSTR(&out), gc);
}