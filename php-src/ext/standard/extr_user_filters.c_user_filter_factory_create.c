#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ uint8_t ;
struct php_user_filter_data {int /*<<< orphan*/ * ce; int /*<<< orphan*/  classname; } ;
struct TYPE_6__ {int /*<<< orphan*/  abstract; } ;
typedef  TYPE_1__ php_stream_filter ;

/* Variables and functions */
 int /*<<< orphan*/  BG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 scalar_t__ IS_FALSE ; 
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_RES (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_property_null (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  add_property_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_property_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  le_userfilters ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ object_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* php_stream_filter_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_filter_free (TYPE_1__*) ; 
 char* safe_emalloc (size_t,int,int) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  user_filter_map ; 
 int /*<<< orphan*/  userfilter_ops ; 
 struct php_user_filter_data* zend_hash_str_find_ptr (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * zend_lookup_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_register_resource (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static php_stream_filter *user_filter_factory_create(const char *filtername,
		zval *filterparams, uint8_t persistent)
{
	struct php_user_filter_data *fdat = NULL;
	php_stream_filter *filter;
	zval obj, zfilter;
	zval func_name;
	zval retval;
	size_t len;

	/* some sanity checks */
	if (persistent) {
		php_error_docref(NULL, E_WARNING,
				"cannot use a user-space filter with a persistent stream");
		return NULL;
	}

	len = strlen(filtername);

	/* determine the classname/class entry */
	if (NULL == (fdat = zend_hash_str_find_ptr(BG(user_filter_map), (char*)filtername, len))) {
		char *period;

		/* Userspace Filters using ambiguous wildcards could cause problems.
           i.e.: myfilter.foo.bar will always call into myfilter.foo.*
                 never seeing myfilter.*
           TODO: Allow failed userfilter creations to continue
                 scanning through the list */
		if ((period = strrchr(filtername, '.'))) {
			char *wildcard = safe_emalloc(len, 1, 3);

			/* Search for wildcard matches instead */
			memcpy(wildcard, filtername, len + 1); /* copy \0 */
			period = wildcard + (period - filtername);
			while (period) {
				ZEND_ASSERT(period[0] == '.');
				period[1] = '*';
				period[2] = '\0';
				if (NULL != (fdat = zend_hash_str_find_ptr(BG(user_filter_map), wildcard, strlen(wildcard)))) {
					period = NULL;
				} else {
					*period = '\0';
					period = strrchr(wildcard, '.');
				}
			}
			efree(wildcard);
		}
		if (fdat == NULL) {
			php_error_docref(NULL, E_WARNING,
					"Err, filter \"%s\" is not in the user-filter map, but somehow the user-filter-factory was invoked for it!?", filtername);
			return NULL;
		}
	}

	/* bind the classname to the actual class */
	if (fdat->ce == NULL) {
		if (NULL == (fdat->ce = zend_lookup_class(fdat->classname))) {
			php_error_docref(NULL, E_WARNING,
					"user-filter \"%s\" requires class \"%s\", but that class is not defined",
					filtername, ZSTR_VAL(fdat->classname));
			return NULL;
		}
	}

	/* create the object */
	if (object_init_ex(&obj, fdat->ce) == FAILURE) {
		return NULL;
	}

	filter = php_stream_filter_alloc(&userfilter_ops, NULL, 0);
	if (filter == NULL) {
		zval_ptr_dtor(&obj);
		return NULL;
	}

	/* filtername */
	add_property_string(&obj, "filtername", (char*)filtername);

	/* and the parameters, if any */
	if (filterparams) {
		add_property_zval(&obj, "params", filterparams);
	} else {
		add_property_null(&obj, "params");
	}

	/* invoke the constructor */
	ZVAL_STRINGL(&func_name, "oncreate", sizeof("oncreate")-1);

	call_user_function(NULL,
			&obj,
			&func_name,
			&retval,
			0, NULL);

	if (Z_TYPE(retval) != IS_UNDEF) {
		if (Z_TYPE(retval) == IS_FALSE) {
			/* User reported filter creation error "return false;" */
			zval_ptr_dtor(&retval);

			/* Kill the filter (safely) */
			ZVAL_UNDEF(&filter->abstract);
			php_stream_filter_free(filter);

			/* Kill the object */
			zval_ptr_dtor(&obj);

			/* Report failure to filter_alloc */
			return NULL;
		}
		zval_ptr_dtor(&retval);
	}
	zval_ptr_dtor(&func_name);

	/* set the filter property, this will be used during cleanup */
	ZVAL_RES(&zfilter, zend_register_resource(filter, le_userfilters));
	ZVAL_OBJ(&filter->abstract, Z_OBJ(obj));
	add_property_zval(&obj, "filter", &zfilter);
	/* add_property_zval increments the refcount which is unwanted here */
	zval_ptr_dtor(&zfilter);

	return filter;
}