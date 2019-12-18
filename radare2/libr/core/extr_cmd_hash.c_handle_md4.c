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
typedef  int /*<<< orphan*/  RHash ;

/* Variables and functions */
 int /*<<< orphan*/  R_HASH_MD4 ; 
 int R_HASH_SIZE_MD4 ; 
 int /*<<< orphan*/  r_cons_newline () ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * r_hash_do_md4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_hash_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_hash_new (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_md4 (const ut8 *block, int len) {
	int i = 0;
	RHash *ctx = r_hash_new (true, R_HASH_MD4);
	const ut8 *c = r_hash_do_md4 (ctx, block, len);
	for (i=0; i<R_HASH_SIZE_MD4; i++) r_cons_printf ("%02x", c[i]);
	r_cons_newline ();
	r_hash_free (ctx);
}