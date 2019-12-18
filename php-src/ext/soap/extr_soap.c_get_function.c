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
typedef  TYPE_1__* sdlPtr ;
typedef  int /*<<< orphan*/ * sdlFunctionPtr ;
struct TYPE_3__ {int /*<<< orphan*/ * requests; int /*<<< orphan*/  functions; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (char*) ; 
 char* estrndup (char const*,int) ; 
 int /*<<< orphan*/  php_strtolower (char*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static sdlFunctionPtr get_function(sdlPtr sdl, const char *function_name) /* {{{ */
{
	sdlFunctionPtr tmp;

	int len = strlen(function_name);
	char *str = estrndup(function_name,len);
	php_strtolower(str,len);
	if (sdl != NULL) {
		if ((tmp = zend_hash_str_find_ptr(&sdl->functions, str, len)) != NULL) {
			efree(str);
			return tmp;
		} else if (sdl->requests != NULL && (tmp = zend_hash_str_find_ptr(sdl->requests, str, len)) != NULL) {
			efree(str);
			return tmp;
		}
	}
	efree(str);
	return NULL;
}