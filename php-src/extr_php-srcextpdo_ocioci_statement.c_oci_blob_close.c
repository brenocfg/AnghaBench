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
typedef  int /*<<< orphan*/  zend_object ;
struct oci_lob_self {struct oci_lob_self* E; int /*<<< orphan*/  dbh; int /*<<< orphan*/  lob; int /*<<< orphan*/  err; int /*<<< orphan*/  svc; TYPE_2__* stmt; } ;
struct TYPE_4__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
struct TYPE_5__ {int /*<<< orphan*/  std; } ;
typedef  TYPE_2__ pdo_stmt_t ;

/* Variables and functions */
 int /*<<< orphan*/  GC_DELREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCILobClose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (struct oci_lob_self*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_blob_close(php_stream *stream, int close_handle)
{
	struct oci_lob_self *self = (struct oci_lob_self *)stream->abstract;
	pdo_stmt_t *stmt = self->stmt;

	if (close_handle) {
		zend_object *obj = &stmt->std;

		OCILobClose(self->E->svc, self->E->err, self->lob);
		zval_ptr_dtor(&self->dbh);
		GC_DELREF(obj);
		efree(self->E);
		efree(self);
	}

	/* php_pdo_free_statement(stmt); */
	return 0;
}