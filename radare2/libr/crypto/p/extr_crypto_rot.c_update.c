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
typedef  int /*<<< orphan*/  RCrypto ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int flag ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_crypto_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rot_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rot_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rot_key ; 

__attribute__((used)) static bool update(RCrypto *cry, const ut8 *buf, int len) {
	ut8 *obuf = calloc (1, len);
	if (!obuf) {
		return false;
	}
	if (flag == 0) {
		rot_crypt (rot_key, buf, obuf, len);
	} else if (flag == 1) {
		rot_decrypt (rot_key, buf, obuf, len);
	}
	r_crypto_append (cry, obuf, len);
	free (obuf);
	return true;
}