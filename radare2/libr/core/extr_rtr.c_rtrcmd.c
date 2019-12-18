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
struct TYPE_3__ {int /*<<< orphan*/  file; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ TextLog ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* r_socket_http_get (char*,int /*<<< orphan*/ *,int*) ; 
 char* r_str_newf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* r_str_uri_encode (char const*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *rtrcmd (TextLog T, const char *str) {
	char *res, *ptr2;
	char *ptr = r_str_uri_encode (str);
	char *uri = r_str_newf ("http://%s:%s/%s%s", T.host, T.port, T.file, ptr? ptr: str);
	int len;
	free (ptr);
	ptr2 = r_socket_http_get (uri, NULL, &len);
	free (uri);
	if (ptr2) {
		ptr2[len] = 0;
		res = strstr (ptr2, "\n\n");
		if (res) {
			res = strstr (res + 1, "\n\n");
		}
		return res? res + 2: ptr2;
	}
	return NULL;
}