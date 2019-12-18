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
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_hash_adler32 (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void handle_adler32 (const ut8 *block, int len) {
	ut32 hn = r_hash_adler32 (block, len);
	ut8 *b = (ut8*)&hn;
	r_cons_printf ("%02x%02x%02x%02x\n", b[0], b[1], b[2], b[3]);
}