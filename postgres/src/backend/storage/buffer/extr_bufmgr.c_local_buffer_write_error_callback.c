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
struct TYPE_3__ {int /*<<< orphan*/  blockNum; int /*<<< orphan*/  forkNum; int /*<<< orphan*/  rnode; } ;
struct TYPE_4__ {TYPE_1__ tag; } ;
typedef  TYPE_2__ BufferDesc ;

/* Variables and functions */
 int /*<<< orphan*/  MyBackendId ; 
 int /*<<< orphan*/  errcontext (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* relpathbackend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
local_buffer_write_error_callback(void *arg)
{
	BufferDesc *bufHdr = (BufferDesc *) arg;

	if (bufHdr != NULL)
	{
		char	   *path = relpathbackend(bufHdr->tag.rnode, MyBackendId,
										  bufHdr->tag.forkNum);

		errcontext("writing block %u of relation %s",
				   bufHdr->tag.blockNum, path);
		pfree(path);
	}
}