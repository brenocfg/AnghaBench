#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_4__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PLyExceptionEntry ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 void* PLy_create_exception (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,char*) ; 
 void* PLy_exc_error ; 
 void* PLy_exc_fatal ; 
 int /*<<< orphan*/  PLy_exc_methods ; 
 int /*<<< orphan*/  PLy_exc_module ; 
 void* PLy_exc_spi_error ; 
 int /*<<< orphan*/  PLy_generate_spi_exceptions (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  PLy_spi_exceptions ; 
 scalar_t__ PyModule_AddObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyModule_Create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_InitModule (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
PLy_add_exceptions(PyObject *plpy)
{
	PyObject   *excmod;
	HASHCTL		hash_ctl;

#if PY_MAJOR_VERSION < 3
	excmod = Py_InitModule("spiexceptions", PLy_exc_methods);
#else
	excmod = PyModule_Create(&PLy_exc_module);
#endif
	if (excmod == NULL)
		PLy_elog(ERROR, "could not create the spiexceptions module");

	/*
	 * PyModule_AddObject does not add a refcount to the object, for some odd
	 * reason; we must do that.
	 */
	Py_INCREF(excmod);
	if (PyModule_AddObject(plpy, "spiexceptions", excmod) < 0)
		PLy_elog(ERROR, "could not add the spiexceptions module");

	PLy_exc_error = PLy_create_exception("plpy.Error", NULL, NULL,
										 "Error", plpy);
	PLy_exc_fatal = PLy_create_exception("plpy.Fatal", NULL, NULL,
										 "Fatal", plpy);
	PLy_exc_spi_error = PLy_create_exception("plpy.SPIError", NULL, NULL,
											 "SPIError", plpy);

	memset(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(int);
	hash_ctl.entrysize = sizeof(PLyExceptionEntry);
	PLy_spi_exceptions = hash_create("PL/Python SPI exceptions", 256,
									 &hash_ctl, HASH_ELEM | HASH_BLOBS);

	PLy_generate_spi_exceptions(excmod, PLy_exc_spi_error);
}