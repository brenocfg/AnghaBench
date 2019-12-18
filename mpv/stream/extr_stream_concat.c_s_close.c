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
struct stream {struct priv* priv; } ;
struct priv {int num_streams; int /*<<< orphan*/ * streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_stream (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s_close(struct stream *s)
{
    struct priv *p = s->priv;

    for (int n = 0; n < p->num_streams; n++)
        free_stream(p->streams[n]);
}