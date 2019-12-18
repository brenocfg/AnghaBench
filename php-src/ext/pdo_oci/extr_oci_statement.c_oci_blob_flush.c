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
struct oci_lob_self {int /*<<< orphan*/  lob; TYPE_1__* E; } ;
struct TYPE_5__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_4__ {int /*<<< orphan*/  err; int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCILobFlushBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oci_blob_flush(php_stream *stream)
{
	struct oci_lob_self *self = (struct oci_lob_self*)stream->abstract;
	OCILobFlushBuffer(self->E->svc, self->E->err, self->lob, 0);
	return 0;
}