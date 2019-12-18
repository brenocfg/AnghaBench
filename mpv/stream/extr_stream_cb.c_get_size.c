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
struct TYPE_4__ {scalar_t__ (* size_fn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  cookie; } ;
struct priv {TYPE_1__ info; } ;
struct TYPE_5__ {struct priv* priv; } ;
typedef  TYPE_2__ stream_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t get_size(stream_t *s)
{
    struct priv *p = s->priv;

    if (p->info.size_fn) {
        int64_t size = p->info.size_fn(p->info.cookie);
        if (size >= 0)
            return size;
    }

    return -1;
}