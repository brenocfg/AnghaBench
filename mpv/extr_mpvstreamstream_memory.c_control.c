#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  start; int /*<<< orphan*/  len; } ;
struct priv {TYPE_3__ data; } ;
struct TYPE_5__ {struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
#define  STREAM_CTRL_GET_SIZE 129 
#define  STREAM_CTRL_SET_CONTENTS 128 
 int STREAM_UNSUPPORTED ; 
 TYPE_3__ bstrdup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int control(stream_t *s, int cmd, void *arg)
{
    struct priv *p = s->priv;
    switch(cmd) {
    case STREAM_CTRL_GET_SIZE:
        *(int64_t *)arg = p->data.len;
        return 1;
    case STREAM_CTRL_SET_CONTENTS: ;
        bstr *data = (bstr *)arg;
        talloc_free(p->data.start);
        p->data = bstrdup(s, *data);
        return 1;
    }
    return STREAM_UNSUPPORTED;
}