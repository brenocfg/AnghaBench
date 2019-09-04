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
struct TYPE_4__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* size_fn ) (int /*<<< orphan*/ ) ;} ;
struct priv {TYPE_1__ info; } ;
struct TYPE_5__ {struct priv* priv; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
#define  STREAM_CTRL_GET_SIZE 128 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int control(stream_t *s, int cmd, void *arg)
{
    struct priv *p = s->priv;
    switch (cmd) {
    case STREAM_CTRL_GET_SIZE: {
        if (!p->info.size_fn)
            break;
        int64_t size = p->info.size_fn(p->info.cookie);
        if (size >= 0) {
            *(int64_t *)arg = size;
            return 1;
        }
        break;
    }
    }
    return STREAM_UNSUPPORTED;
}