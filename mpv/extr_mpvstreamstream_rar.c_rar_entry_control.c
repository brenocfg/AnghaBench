#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  size; TYPE_1__* s; } ;
typedef  TYPE_3__ rar_file_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  url; } ;

/* Variables and functions */
#define  STREAM_CTRL_GET_BASE_FILENAME 129 
#define  STREAM_CTRL_GET_SIZE 128 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 char* talloc_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rar_entry_control(stream_t *s, int cmd, void *arg)
{
    rar_file_t *rar_file = s->priv;
    switch (cmd) {
    case STREAM_CTRL_GET_BASE_FILENAME:
        *(char **)arg = talloc_strdup(NULL, rar_file->s->url);
        return STREAM_OK;
    case STREAM_CTRL_GET_SIZE:
        *(int64_t *)arg = rar_file->size;
        return STREAM_OK;
    }
    return STREAM_UNSUPPORTED;
}