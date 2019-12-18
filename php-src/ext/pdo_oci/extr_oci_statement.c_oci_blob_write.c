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
typedef  scalar_t__ ub4 ;
typedef  scalar_t__ sword ;
struct oci_lob_self {int /*<<< orphan*/  offset; int /*<<< orphan*/  lob; TYPE_1__* E; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_4__ {int /*<<< orphan*/  err; int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 scalar_t__ OCILobWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI_ONE_PIECE ; 
 scalar_t__ OCI_SUCCESS ; 
 int /*<<< orphan*/  SQLCS_IMPLICIT ; 

__attribute__((used)) static ssize_t oci_blob_write(php_stream *stream, const char *buf, size_t count)
{
	struct oci_lob_self *self = (struct oci_lob_self*)stream->abstract;
	ub4 amt;
	sword r;

	amt = (ub4) count;
	r = OCILobWrite(self->E->svc, self->E->err, self->lob,
		&amt, self->offset, (char*)buf, (ub4) count,
		OCI_ONE_PIECE,
		NULL, NULL, 0, SQLCS_IMPLICIT);

	if (r != OCI_SUCCESS) {
		return (ssize_t)-1;
	}

	self->offset += amt;
	return amt;
}