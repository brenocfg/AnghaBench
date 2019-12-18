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
struct TYPE_4__ {int /*<<< orphan*/  file_name; int /*<<< orphan*/  context; int /*<<< orphan*/  flags; int /*<<< orphan*/  access; TYPE_1__ hdr; } ;
typedef  TYPE_2__ open_file_task_t ;
typedef  int /*<<< orphan*/  ftp_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTP_FtpOpenFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AsyncFtpOpenFileProc(task_header_t *hdr)
{
    open_file_task_t *task = (open_file_task_t*)hdr;
    ftp_session_t *session = (ftp_session_t*)task->hdr.hdr;

    TRACE("%p\n", session);

    FTP_FtpOpenFileW(session, task->file_name, task->access, task->flags, task->context);
    heap_free(task->file_name);
}