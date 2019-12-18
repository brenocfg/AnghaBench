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

/* Variables and functions */
 int EVP_PKEY_DSA ; 
 int EVP_PKEY_EC ; 
 int EVP_PKEY_RSA ; 
 int EVP_PKEY_RSA_PSS ; 
 int NID_undef ; 
 int OBJ_ln2nid (char const*) ; 
 int OBJ_sn2nid (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void get_sigorhash(int *psig, int *phash, const char *str)
{
    if (strcmp(str, "RSA") == 0) {
        *psig = EVP_PKEY_RSA;
    } else if (strcmp(str, "RSA-PSS") == 0 || strcmp(str, "PSS") == 0) {
        *psig = EVP_PKEY_RSA_PSS;
    } else if (strcmp(str, "DSA") == 0) {
        *psig = EVP_PKEY_DSA;
    } else if (strcmp(str, "ECDSA") == 0) {
        *psig = EVP_PKEY_EC;
    } else {
        *phash = OBJ_sn2nid(str);
        if (*phash == NID_undef)
            *phash = OBJ_ln2nid(str);
    }
}