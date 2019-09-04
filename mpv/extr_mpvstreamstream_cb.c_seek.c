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
struct TYPE_4__ {scalar_t__ (* seek_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cookie; } ;
struct priv {TYPE_1__ info; } ;
struct TYPE_5__ {struct priv* priv; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seek(stream_t *s, int64_t newpos)
{
    struct priv *p = s->priv;
    return p->info.seek_fn(p->info.cookie, newpos) >= 0;
}