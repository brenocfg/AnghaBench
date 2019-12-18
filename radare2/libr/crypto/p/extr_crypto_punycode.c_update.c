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
 scalar_t__ flag ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_crypto_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* r_punycode_decode (char const*,int,int*) ; 
 char* r_punycode_encode (int /*<<< orphan*/  const*,int,int*) ; 

__attribute__((used)) static bool update(RCrypto *cry, const ut8 *buf, int len) {
	char *obuf;
	int olen;
	if (flag) {
		obuf = r_punycode_decode ((const char *)buf, len, &olen);
	} else {
		obuf = r_punycode_encode (buf, len, &olen);
	}
	r_crypto_append (cry, (ut8*)obuf, olen);
	free (obuf);
	return true;
}