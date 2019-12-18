#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
struct oci_lob_self {int offset; int /*<<< orphan*/  dbh; TYPE_4__* S; TYPE_2__* E; TYPE_3__* stmt; int /*<<< orphan*/ * lob; } ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_8__ {int /*<<< orphan*/  std; scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_stmt_t ;
struct TYPE_9__ {int /*<<< orphan*/  err; TYPE_1__* H; } ;
typedef  TYPE_4__ pdo_oci_stmt ;
typedef  int /*<<< orphan*/  oci_lob_env ;
struct TYPE_7__ {int /*<<< orphan*/  err; int /*<<< orphan*/  svc; } ;
struct TYPE_6__ {int /*<<< orphan*/  svc; } ;
typedef  int /*<<< orphan*/  OCILobLocator ;

/* Variables and functions */
 int /*<<< orphan*/  GC_ADDREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ADDREF (int /*<<< orphan*/ ) ; 
 void* ecalloc (int,int) ; 
 int /*<<< orphan*/  efree (struct oci_lob_self*) ; 
 int /*<<< orphan*/  oci_blob_stream_ops ; 
 int /*<<< orphan*/ * php_stream_alloc (int /*<<< orphan*/ *,struct oci_lob_self*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static php_stream *oci_create_lob_stream(zval *dbh, pdo_stmt_t *stmt, OCILobLocator *lob)
{
	php_stream *stm;
	struct oci_lob_self *self = ecalloc(1, sizeof(*self));

	ZVAL_COPY_VALUE(&self->dbh, dbh);
	self->lob = lob;
	self->offset = 1; /* 1-based */
	self->stmt = stmt;
	self->S = (pdo_oci_stmt*)stmt->driver_data;
	self->E = ecalloc(1, sizeof(oci_lob_env));
	self->E->svc = self->S->H->svc;
	self->E->err = self->S->err;

	stm = php_stream_alloc(&oci_blob_stream_ops, self, 0, "r+b");

	if (stm) {
		zend_object *obj;
		obj = &stmt->std;
		Z_ADDREF(self->dbh);
		GC_ADDREF(obj);
		return stm;
	}

	efree(self);
	return NULL;
}