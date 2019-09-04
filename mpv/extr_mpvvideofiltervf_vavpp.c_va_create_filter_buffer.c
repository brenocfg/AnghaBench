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
struct priv {int /*<<< orphan*/  context; int /*<<< orphan*/  display; } ;
struct mp_filter {struct priv* priv; } ;
typedef  int /*<<< orphan*/  VAStatus ;
typedef  int /*<<< orphan*/  VABufferID ;

/* Variables and functions */
 scalar_t__ CHECK_VA_STATUS (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  VAProcFilterParameterBufferType ; 
 int /*<<< orphan*/  VA_INVALID_ID ; 
 int /*<<< orphan*/  vaCreateBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VABufferID va_create_filter_buffer(struct mp_filter *vf, int bytes,
                                          int num, void *data)
{
    struct priv *p = vf->priv;
    VABufferID buffer;
    VAStatus status = vaCreateBuffer(p->display, p->context,
                                     VAProcFilterParameterBufferType,
                                     bytes, num, data, &buffer);
    return CHECK_VA_STATUS(vf, "vaCreateBuffer()") ? buffer : VA_INVALID_ID;
}