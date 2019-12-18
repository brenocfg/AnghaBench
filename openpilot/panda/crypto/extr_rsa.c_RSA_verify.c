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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ len; int exponent; } ;
typedef  TYPE_1__ RSAPublicKey ;

/* Variables and functions */
 int RSANUMBYTES ; 
 scalar_t__ RSANUMWORDS ; 
 int const SHA_DIGEST_SIZE ; 
 int /*<<< orphan*/  modpow (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* sha_padding_1024 ; 

int RSA_verify(const RSAPublicKey *key,
               const uint8_t *signature,
               const int len,
               const uint8_t *hash,
               const int hash_len) {
    uint8_t buf[RSANUMBYTES];
    int i;
    //const uint8_t* padding_hash;

    if (key->len != RSANUMWORDS) {
        return 0;  // Wrong key passed in.
    }

    if (len != sizeof(buf)) {
        return 0;  // Wrong input length.
    }

    if (hash_len != SHA_DIGEST_SIZE) {
        return 0;  // Unsupported hash.
    }

    if (key->exponent != 3 && key->exponent != 65537) {
        return 0;  // Unsupported exponent.
    }

    for (i = 0; i < len; ++i) {  // Copy input to local workspace.
        buf[i] = signature[i];
    }

    modpow(key, buf);  // In-place exponentiation.

#ifdef TEST_RSA
    printf("sig\n");
    for (i=0;i<len;i++) { if(i!=0 && i%0x10 == 0) printf("\n"); printf("%02X ", signature[i]); } printf("\n");
    printf("hash\n");
    for (i=0;i<hash_len;i++) { if(i!=0 && i%0x10 == 0) printf("\n"); printf("%02X ", hash[i]); } printf("\n");
    printf("out\n");
    for (i=0;i<RSANUMBYTES;i++) { if(i!=0 && i%0x10 == 0) printf("\n"); printf("%02X ", buf[i]); } printf("\n");
    printf("target\n");
    for (i=0;i<RSANUMBYTES;i++) { if(i!=0 && i%0x10 == 0) printf("\n"); printf("%02X ", sha_padding_1024[i]); } printf("\n");
#endif

    // Xor sha portion, so it all becomes 00 iff equal.
    for (i = len - hash_len; i < len; ++i) {
        buf[i] ^= *hash++;
    }

    // Hash resulting buf, in-place.
    /*switch (hash_len) {
        case SHA_DIGEST_SIZE:
            padding_hash = kExpectedPadShaRsa2048;
            SHA_hash(buf, len, buf);
            break;
        default:
            return 0;
    }


    // Compare against expected hash value.
    for (i = 0; i < hash_len; ++i) {
        if (buf[i] != padding_hash[i]) {
            return 0;
        }
    }*/

    for (i = 0; i < RSANUMBYTES; ++i) {
        if (buf[i] != sha_padding_1024[i]) {
            return 0;
        }
    }

    return 1;  // All checked out OK.
}