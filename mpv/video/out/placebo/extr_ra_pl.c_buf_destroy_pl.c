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
struct ra_buf {int /*<<< orphan*/  priv; } ;
struct ra {int dummy; } ;
struct pl_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_gpu (struct ra*) ; 
 int /*<<< orphan*/  pl_buf_destroy (int /*<<< orphan*/ ,struct pl_buf const**) ; 
 int /*<<< orphan*/  talloc_free (struct ra_buf*) ; 

__attribute__((used)) static void buf_destroy_pl(struct ra *ra, struct ra_buf *buf)
{
    if (!buf)
        return;

    pl_buf_destroy(get_gpu(ra), (const struct pl_buf **) &buf->priv);
    talloc_free(buf);
}