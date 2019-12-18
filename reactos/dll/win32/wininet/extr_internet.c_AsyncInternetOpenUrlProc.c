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
struct TYPE_4__ {int /*<<< orphan*/  headers; int /*<<< orphan*/  url; int /*<<< orphan*/  context; int /*<<< orphan*/  flags; int /*<<< orphan*/  headers_len; TYPE_1__ hdr; } ;
typedef  TYPE_2__ open_url_task_t ;
typedef  int /*<<< orphan*/  appinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNET_InternetOpenUrlW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AsyncInternetOpenUrlProc(task_header_t *hdr)
{
    open_url_task_t *task = (open_url_task_t*)hdr;

    TRACE("%p\n", task->hdr.hdr);

    INTERNET_InternetOpenUrlW((appinfo_t*)task->hdr.hdr, task->url, task->headers,
            task->headers_len, task->flags, task->context);
    heap_free(task->url);
    heap_free(task->headers);
}