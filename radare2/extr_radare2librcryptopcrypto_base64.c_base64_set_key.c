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
struct TYPE_3__ {int dir; } ;
typedef  TYPE_1__ RCrypto ;

/* Variables and functions */

__attribute__((used)) static bool base64_set_key(RCrypto *cry, const ut8 *key, int keylen, int mode, int direction) {
	cry->dir = direction;
	return true;
}