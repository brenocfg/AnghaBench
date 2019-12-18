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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_3__ {int dir; } ;
typedef  TYPE_1__ RCrypto ;

/* Variables and functions */
 int /*<<< orphan*/ * cps2key ; 
 int /*<<< orphan*/  r_read_be32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool set_key(RCrypto *cry, const ut8 *key, int keylen, int mode, int direction) {
	cry->dir = direction;
	if (keylen == 8) {
		/* fix key endianness */
		const ut32 *key32 = (const ut32*)key;
		cps2key[0] = r_read_be32 (key32);
		cps2key[1] = r_read_be32 (key32 + 1);
		return true;
	}
	return false;
}