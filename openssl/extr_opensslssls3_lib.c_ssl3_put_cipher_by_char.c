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
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_3__ {int id; } ;
typedef  TYPE_1__ SSL_CIPHER ;

/* Variables and functions */
 int SSL3_CK_CIPHERSUITE_FLAG ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int) ; 

int ssl3_put_cipher_by_char(const SSL_CIPHER *c, WPACKET *pkt, size_t *len)
{
    if ((c->id & 0xff000000) != SSL3_CK_CIPHERSUITE_FLAG) {
        *len = 0;
        return 1;
    }

    if (!WPACKET_put_bytes_u16(pkt, c->id & 0xffff))
        return 0;

    *len = 2;
    return 1;
}