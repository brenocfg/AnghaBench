#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SSL_CIPHER ;

/* Variables and functions */
 TYPE_1__ const* OBJ_bsearch_ssl_cipher_id (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL3_NUM_CIPHERS ; 
 int /*<<< orphan*/  SSL3_NUM_SCSVS ; 
 int /*<<< orphan*/  TLS13_NUM_CIPHERS ; 
 int /*<<< orphan*/  ssl3_ciphers ; 
 int /*<<< orphan*/  ssl3_scsvs ; 
 int /*<<< orphan*/  tls13_ciphers ; 

const SSL_CIPHER *ssl3_get_cipher_by_id(uint32_t id)
{
    SSL_CIPHER c;
    const SSL_CIPHER *cp;

    c.id = id;
    cp = OBJ_bsearch_ssl_cipher_id(&c, tls13_ciphers, TLS13_NUM_CIPHERS);
    if (cp != NULL)
        return cp;
    cp = OBJ_bsearch_ssl_cipher_id(&c, ssl3_ciphers, SSL3_NUM_CIPHERS);
    if (cp != NULL)
        return cp;
    return OBJ_bsearch_ssl_cipher_id(&c, ssl3_scsvs, SSL3_NUM_SCSVS);
}