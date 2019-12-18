#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_header_t ;
struct TYPE_3__ {scalar_t__ hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  headers; int /*<<< orphan*/  end_request; int /*<<< orphan*/  content_len; int /*<<< orphan*/  optional_len; int /*<<< orphan*/  optional; int /*<<< orphan*/  headers_len; TYPE_1__ hdr; } ;
typedef  TYPE_2__ send_request_task_t ;
typedef  int /*<<< orphan*/  http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_HttpSendRequestW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AsyncHttpSendRequestProc(task_header_t *hdr)
{
    send_request_task_t *task = (send_request_task_t*)hdr;
    http_request_t *request = (http_request_t*)task->hdr.hdr;

    TRACE("%p\n", request);

    HTTP_HttpSendRequestW(request, task->headers, task->headers_len, task->optional,
            task->optional_len, task->content_len, task->end_request);

    heap_free(task->headers);
}