#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  php_com_dotnet_object ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 int /*<<< orphan*/  efree (char*) ; 
 int php_com_do_invoke_by_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_com_get_id_of_name (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_com_throw_exception (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_win32_error_msg_free (char*) ; 
 char* php_win32_error_to_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,char*,char*) ; 

int php_com_do_invoke(php_com_dotnet_object *obj, char *name, size_t namelen,
		WORD flags,	VARIANT *v, int nargs, zval *args, int allow_noarg)
{
	DISPID dispid;
	HRESULT hr;
	char *msg = NULL;

	hr = php_com_get_id_of_name(obj, name, namelen, &dispid);

	if (FAILED(hr)) {
		char *winerr = php_win32_error_to_msg(hr);
		spprintf(&msg, 0, "Unable to lookup `%s': %s", name, winerr);
		php_win32_error_msg_free(winerr);
		php_com_throw_exception(hr, msg);
		efree(msg);
		return FAILURE;
	}

	return php_com_do_invoke_by_id(obj, dispid, flags, v, nargs, args, 0, allow_noarg);
}