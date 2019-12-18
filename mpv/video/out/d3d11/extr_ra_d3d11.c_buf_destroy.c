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
struct d3d_buf {int /*<<< orphan*/  uav; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct ra_buf*) ; 

__attribute__((used)) static void buf_destroy(struct ra *ra, struct ra_buf *buf)
{
    if (!buf)
        return;
    struct d3d_buf *buf_p = buf->priv;
    SAFE_RELEASE(buf_p->buf);
    SAFE_RELEASE(buf_p->uav);
    talloc_free(buf);
}