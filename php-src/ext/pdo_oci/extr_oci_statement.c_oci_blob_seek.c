#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_off_t ;
typedef  scalar_t__ ub4 ;
struct oci_lob_self {scalar_t__ offset; } ;
struct TYPE_3__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;

/* Variables and functions */
 scalar_t__ PDO_OCI_LOBMAXSIZE ; 

__attribute__((used)) static int oci_blob_seek(php_stream *stream, zend_off_t offset, int whence, zend_off_t *newoffset)
{
	struct oci_lob_self *self = (struct oci_lob_self*)stream->abstract;

	if (offset >= PDO_OCI_LOBMAXSIZE) {
		return -1;
	} else {
		self->offset = (ub4) offset + 1;  /* Oracle LOBS are 1-based, but PHP is 0-based */
		return 0;
	}
}