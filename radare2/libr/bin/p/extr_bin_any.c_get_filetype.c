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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RMagic ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  R2_SDB_MAGIC ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* r_magic_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_magic_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_magic_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_magic_new (int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *get_filetype(RBuffer *b) {
	ut8 buf[4096] = { 0 };
	char *res = NULL;
	RMagic *ck = r_magic_new (0);
	if (!ck) {
		return NULL;
	}
	const char *tmp = NULL;
	// TODO: dir.magic not honored here
	r_magic_load (ck, R2_SDB_MAGIC);
	r_buf_read_at (b, 0, buf, sizeof (buf));
	tmp = r_magic_buffer (ck, buf, sizeof (buf));
	if (tmp) {
		res = strdup (tmp);
	}
	r_magic_free (ck);
	return res;
}