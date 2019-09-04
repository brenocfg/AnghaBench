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
struct priv {int /*<<< orphan*/  entry_size; TYPE_1__* src; } ;
struct TYPE_5__ {struct priv* priv; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  url; } ;

/* Variables and functions */
#define  STREAM_CTRL_GET_BASE_FILENAME 129 
#define  STREAM_CTRL_GET_SIZE 128 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 char* talloc_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int archive_entry_control(stream_t *s, int cmd, void *arg)
{
    struct priv *p = s->priv;
    switch (cmd) {
    case STREAM_CTRL_GET_BASE_FILENAME:
        *(char **)arg = talloc_strdup(NULL, p->src->url);
        return STREAM_OK;
    case STREAM_CTRL_GET_SIZE:
        if (p->entry_size < 0)
            break;
        *(int64_t *)arg = p->entry_size;
        return STREAM_OK;
    }
    return STREAM_UNSUPPORTED;
}