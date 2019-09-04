#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut16 ;
struct TYPE_4__ {int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ RCrypto ;

/* Variables and functions */
 int /*<<< orphan*/  UPPER_LIMIT ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  cps2_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cps2key ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_crypto_append (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool update(RCrypto *cry, const ut8 *buf, int len) {
	ut8 *output = calloc (1, len);
	/* TODO : control decryption errors */
	cps2_crypt (cry->dir, (const ut16 *)buf, (ut16*)output, len, cps2key, UPPER_LIMIT);
	r_crypto_append (cry, output, len);
	free (output);
	return true;
}