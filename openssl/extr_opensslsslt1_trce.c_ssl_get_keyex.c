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
struct TYPE_6__ {unsigned long algorithm_mkey; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 unsigned long SSL_kDHE ; 
 unsigned long SSL_kDHEPSK ; 
 unsigned long SSL_kECDHE ; 
 unsigned long SSL_kECDHEPSK ; 
 unsigned long SSL_kGOST ; 
 unsigned long SSL_kPSK ; 
 unsigned long SSL_kRSA ; 
 unsigned long SSL_kRSAPSK ; 
 unsigned long SSL_kSRP ; 

__attribute__((used)) static int ssl_get_keyex(const char **pname, const SSL *ssl)
{
    unsigned long alg_k = ssl->s3.tmp.new_cipher->algorithm_mkey;

    if (alg_k & SSL_kRSA) {
        *pname = "rsa";
        return SSL_kRSA;
    }
    if (alg_k & SSL_kDHE) {
        *pname = "DHE";
        return SSL_kDHE;
    }
    if (alg_k & SSL_kECDHE) {
        *pname = "ECDHE";
        return SSL_kECDHE;
    }
    if (alg_k & SSL_kPSK) {
        *pname = "PSK";
        return SSL_kPSK;
    }
    if (alg_k & SSL_kRSAPSK) {
        *pname = "RSAPSK";
        return SSL_kRSAPSK;
    }
    if (alg_k & SSL_kDHEPSK) {
        *pname = "DHEPSK";
        return SSL_kDHEPSK;
    }
    if (alg_k & SSL_kECDHEPSK) {
        *pname = "ECDHEPSK";
        return SSL_kECDHEPSK;
    }
    if (alg_k & SSL_kSRP) {
        *pname = "SRP";
        return SSL_kSRP;
    }
    if (alg_k & SSL_kGOST) {
        *pname = "GOST";
        return SSL_kGOST;
    }
    *pname = "UNKNOWN";
    return 0;
}