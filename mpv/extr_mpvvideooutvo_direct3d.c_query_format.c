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
struct vo {int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  d3d_priv ;

/* Variables and functions */
 int /*<<< orphan*/  init_rendering_mode (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int query_format(struct vo *vo, int movie_fmt)
{
    d3d_priv *priv = vo->priv;
    if (!init_rendering_mode(priv, movie_fmt, false))
        return 0;

    return 1;
}