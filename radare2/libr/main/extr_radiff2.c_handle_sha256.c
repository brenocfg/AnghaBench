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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  RHash ;

/* Variables and functions */
 int /*<<< orphan*/  R_HASH_SHA256 ; 
 int R_HASH_SIZE_SHA256 ; 
 int /*<<< orphan*/  printf (char*,int const) ; 
 int* r_hash_do_sha256 (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  r_hash_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_hash_new (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_sha256(const ut8 *block, int len) {
	int i = 0;
	RHash *ctx = r_hash_new (true, R_HASH_SHA256);
	const ut8 *c = r_hash_do_sha256 (ctx, block, len);
	if (!c) {
		r_hash_free (ctx);
		return;
	}
	for (i = 0; i < R_HASH_SIZE_SHA256; i++) {
		printf ("%02x", c[i]);
	}
	r_hash_free (ctx);
}