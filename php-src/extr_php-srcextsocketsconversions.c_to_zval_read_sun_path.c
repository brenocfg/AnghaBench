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
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
typedef  int /*<<< orphan*/  res_context ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_to_zval_err (int /*<<< orphan*/ *,char*) ; 
 char* memchr (int /*<<< orphan*/ *,char,int) ; 

__attribute__((used)) static void to_zval_read_sun_path(const char *data, zval *zv, res_context *ctx) {
	struct sockaddr_un	*saddr = (struct sockaddr_un*)data;
	char *nul_pos;

	nul_pos = memchr(&saddr->sun_path, '\0', sizeof(saddr->sun_path));
	if (nul_pos == NULL) {
		do_to_zval_err(ctx, "could not find a NUL in the path");
		return;
	}

	ZVAL_STRINGL(zv, saddr->sun_path, nul_pos - (char*)&saddr->sun_path);
}