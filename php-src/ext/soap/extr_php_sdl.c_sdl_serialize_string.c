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
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int /*<<< orphan*/  WSDL_CACHE_PUT_INT (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WSDL_CACHE_PUT_N (char const*,int,int /*<<< orphan*/ *) ; 
 int WSDL_NO_STRING_MARKER ; 
 int strlen (char const*) ; 

__attribute__((used)) static void sdl_serialize_string(const char *str, smart_str *out)
{
	if (str) {
		int i = strlen(str);
		WSDL_CACHE_PUT_INT(i, out);
		if (i > 0) {
			WSDL_CACHE_PUT_N(str, i, out);
		}
	} else {
		WSDL_CACHE_PUT_INT(WSDL_NO_STRING_MARKER, out);
	}
}