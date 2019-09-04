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
typedef  size_t ub4 ;
typedef  scalar_t__ sword ;
struct oci_lob_self {size_t offset; int /*<<< orphan*/  lob; TYPE_1__* E; } ;
struct TYPE_5__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_4__ {int /*<<< orphan*/  err; int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 scalar_t__ OCILobRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OCI_NEED_DATA ; 
 scalar_t__ OCI_SUCCESS ; 
 int /*<<< orphan*/  SQLCS_IMPLICIT ; 

__attribute__((used)) static size_t oci_blob_read(php_stream *stream, char *buf, size_t count)
{
	struct oci_lob_self *self = (struct oci_lob_self*)stream->abstract;
	ub4 amt;
	sword r;

	amt = (ub4) count;
	r = OCILobRead(self->E->svc, self->E->err, self->lob,
		&amt, self->offset, buf, (ub4) count,
		NULL, NULL, 0, SQLCS_IMPLICIT);

	if (r != OCI_SUCCESS && r != OCI_NEED_DATA) {
		return (size_t)-1;
	}

	self->offset += amt;
	if (amt < count) {
		stream->eof = 1;
	}
	return amt;
}