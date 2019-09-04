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
typedef  char ut8 ;
struct TYPE_4__ {int dir; } ;
typedef  TYPE_1__ RCrypto ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int r_base64_decode (char*,char const*,int) ; 
 int /*<<< orphan*/  r_base64_encode (char*,char const*,int) ; 
 int /*<<< orphan*/  r_crypto_append (TYPE_1__*,char*,int) ; 

__attribute__((used)) static bool update(RCrypto *cry, const ut8 *buf, int len) {
	int olen = 0;
	ut8 *obuf = NULL;
	if (cry->dir == 0) {
		olen = ((len + 2) / 3 ) * 4;
		obuf = malloc (olen + 1);
		if (!obuf) {
			return false;
		}
		r_base64_encode ((char *)obuf, (const ut8 *)buf, len);
	} else if (cry->dir == 1) {
		olen = 4 + ((len / 4) * 3);
		if (len > 0) {
			olen -= (buf[len-1] == '=') ? ((buf[len-2] == '=') ? 2 : 1) : 0;
		}
		obuf = malloc (olen + 4);
		if (!obuf) {
			return false;
		}
		olen = r_base64_decode (obuf, (const char *)buf, len);
	}
	if (olen > 0) {
		r_crypto_append (cry, obuf, olen);
	}
	free (obuf);
	return true;
}