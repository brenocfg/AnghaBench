#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* new_cipher; } ;
struct TYPE_8__ {TYPE_2__ tmp; } ;
struct TYPE_9__ {TYPE_3__ s3; } ;
struct TYPE_6__ {long algorithm_mkey; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 long SSL_kDHE ; 
 long SSL_kDHEPSK ; 
 long SSL_kECDHE ; 
 long SSL_kECDHEPSK ; 
 long SSL_kSRP ; 

__attribute__((used)) static int key_exchange_expected(SSL *s)
{
    long alg_k = s->s3.tmp.new_cipher->algorithm_mkey;

    /*
     * Can't skip server key exchange if this is an ephemeral
     * ciphersuite or for SRP
     */
    if (alg_k & (SSL_kDHE | SSL_kECDHE | SSL_kDHEPSK | SSL_kECDHEPSK
                 | SSL_kSRP)) {
        return 1;
    }

    return 0;
}