#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  shkeybag; } ;
struct TYPE_5__ {TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ PKCS12_SAFEBAG ;

/* Variables and functions */
 int /*<<< orphan*/ * PKCS8_decrypt (int /*<<< orphan*/ ,char const*,int) ; 

PKCS8_PRIV_KEY_INFO *PKCS12_decrypt_skey(const PKCS12_SAFEBAG *bag,
                                         const char *pass, int passlen)
{
    return PKCS8_decrypt(bag->value.shkeybag, pass, passlen);
}