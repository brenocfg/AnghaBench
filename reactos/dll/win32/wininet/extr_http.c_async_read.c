#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void** ret_read; int /*<<< orphan*/  hdr; void* read_pos; void* size; void* buf; } ;
typedef  TYPE_1__ read_file_task_t ;
struct TYPE_6__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_2__ http_request_t ;
typedef  void* DWORD ;

/* Variables and functions */
 void* ERROR_IO_PENDING ; 
 void* ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  INTERNET_AsyncCall (int /*<<< orphan*/ *) ; 
 TYPE_1__* alloc_async_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  async_read_file_proc ; 

__attribute__((used)) static DWORD async_read(http_request_t *req, void *buf, DWORD size, DWORD read_pos, DWORD *ret_read)
{
    read_file_task_t *task;

    task = alloc_async_task(&req->hdr, async_read_file_proc, sizeof(*task));
    if(!task)
        return ERROR_OUTOFMEMORY;

    task->buf = buf;
    task->size = size;
    task->read_pos = read_pos;
    task->ret_read = ret_read;

    INTERNET_AsyncCall(&task->hdr);
    return ERROR_IO_PENDING;
}