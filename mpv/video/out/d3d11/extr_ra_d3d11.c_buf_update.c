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
struct ra_buf {struct d3d_buf* priv; } ;
struct ra {int dummy; } ;
struct d3d_buf {char* data; int dirty; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 

__attribute__((used)) static void buf_update(struct ra *ra, struct ra_buf *buf, ptrdiff_t offset,
                       const void *data, size_t size)
{
    struct d3d_buf *buf_p = buf->priv;

    char *cdata = buf_p->data;
    memcpy(cdata + offset, data, size);
    buf_p->dirty = true;
}