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
typedef  int /*<<< orphan*/  VAProcFilterType ;

/* Variables and functions */
 scalar_t__ CHECK_VA_STATUS (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  vaQueryVideoProcFilterCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int*) ; 

__attribute__((used)) static int va_query_filter_caps(struct mp_filter *vf, VAProcFilterType type,
                                void *caps, unsigned int count)
{
    struct priv *p = vf->priv;
    VAStatus status = vaQueryVideoProcFilterCaps(p->display, p->context, type,
                                                 caps, &count);
    return CHECK_VA_STATUS(vf, "vaQueryVideoProcFilterCaps()") ? count : 0;
}