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
struct TYPE_4__ {int dir; } ;
typedef  TYPE_1__ RCrypto ;

/* Variables and functions */
 int INSIZE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int r_base91_decode (int /*<<< orphan*/ *,char const*,int) ; 
 int r_base91_encode (char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_crypto_append (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool update(RCrypto *cry, const ut8 *buf, int len) {
	int olen = INSIZE;
	if (!cry || !buf || len < 1) {
		return false;
	}
	ut8 *obuf = malloc (olen);
	if (!obuf) {
		return false;
	}
	if (cry->dir == 0) {
		olen = r_base91_encode ((char *)obuf, (const ut8 *)buf, len);
	} else if (cry->dir == 1) {
		olen = r_base91_decode (obuf, (const char *)buf, len);
	}
	r_crypto_append (cry, obuf, olen);
	free (obuf);
	return true;
}