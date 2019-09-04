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
typedef  int /*<<< orphan*/  PKCS12 ;

/* Variables and functions */
 int pkcs12_gen_mac (int /*<<< orphan*/ *,char const*,int,unsigned char*,unsigned int*,int /*<<< orphan*/ *) ; 

int PKCS12_gen_mac(PKCS12 *p12, const char *pass, int passlen,
                   unsigned char *mac, unsigned int *maclen)
{
    return pkcs12_gen_mac(p12, pass, passlen, mac, maclen, NULL);
}