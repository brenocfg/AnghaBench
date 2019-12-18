#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ priv; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  cd; int /*<<< orphan*/  cdp; } ;
typedef  TYPE_2__ cdda_priv ;

/* Variables and functions */
 int /*<<< orphan*/  cdda_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paranoia_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_cdda(stream_t *s)
{
    cdda_priv *p = (cdda_priv *)s->priv;
    paranoia_free(p->cdp);
    cdda_close(p->cd);
}