#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* zval ;
struct TYPE_8__ {void* name; void* value; } ;
typedef  TYPE_1__ zend_constant ;
typedef  int /*<<< orphan*/  php_stream_context ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_CS ; 
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_STREAM_FLAG_NO_CLOSE ; 
 int /*<<< orphan*/  ZEND_CONSTANT_SET_FLAGS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_STRL (char*) ; 
 int /*<<< orphan*/  php_stream_close (TYPE_2__*) ; 
 TYPE_2__* php_stream_open_wrapper_ex (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_to_zval (TYPE_2__*,void**) ; 
 int /*<<< orphan*/  zend_constants ; 
 int /*<<< orphan*/  zend_hash_del (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  zend_register_constant (TYPE_1__*) ; 
 void* zend_string_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void phpdbg_register_file_handles(void) /* {{{ */
{
	zval zin, zout, zerr;
	php_stream *s_in, *s_out, *s_err;
	php_stream_context *sc_in=NULL, *sc_out=NULL, *sc_err=NULL;
	zend_constant ic, oc, ec;

	s_in  = php_stream_open_wrapper_ex("php://stdin",  "rb", 0, NULL, sc_in);
	s_out = php_stream_open_wrapper_ex("php://stdout", "wb", 0, NULL, sc_out);
	s_err = php_stream_open_wrapper_ex("php://stderr", "wb", 0, NULL, sc_err);

	if (s_in==NULL || s_out==NULL || s_err==NULL) {
		if (s_in) php_stream_close(s_in);
		if (s_out) php_stream_close(s_out);
		if (s_err) php_stream_close(s_err);
		return;
	}

#if PHP_DEBUG
	/* do not close stdout and stderr */
	s_out->flags |= PHP_STREAM_FLAG_NO_CLOSE;
	s_err->flags |= PHP_STREAM_FLAG_NO_CLOSE;
#endif

	php_stream_to_zval(s_in,  &zin);
	php_stream_to_zval(s_out, &zout);
	php_stream_to_zval(s_err, &zerr);

	ic.value = zin;
	ZEND_CONSTANT_SET_FLAGS(&ic, CONST_CS, 0);
	ic.name = zend_string_init(ZEND_STRL("STDIN"), 0);
	zend_hash_del(EG(zend_constants), ic.name);
	zend_register_constant(&ic);

	oc.value = zout;
	ZEND_CONSTANT_SET_FLAGS(&oc, CONST_CS, 0);
	oc.name = zend_string_init(ZEND_STRL("STDOUT"), 0);
	zend_hash_del(EG(zend_constants), oc.name);
	zend_register_constant(&oc);

	ec.value = zerr;
	ZEND_CONSTANT_SET_FLAGS(&ec, CONST_CS, 0);
	ec.name = zend_string_init(ZEND_STRL("STDERR"), 0);
	zend_hash_del(EG(zend_constants), ec.name);
	zend_register_constant(&ec);
}