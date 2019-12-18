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
struct TYPE_4__ {int /*<<< orphan*/ * iana_name; int /*<<< orphan*/ * openssl_name; } ;
typedef  TYPE_1__ tls_cipher_name_pair ;

/* Variables and functions */
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ *,size_t) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 TYPE_1__* tls_cipher_name_translation_table ; 

const tls_cipher_name_pair *
tls_get_cipher_name_pair(const char *cipher_name, size_t len)
{
    const tls_cipher_name_pair *pair = tls_cipher_name_translation_table;

    while (pair->openssl_name != NULL)
    {
        if ((strlen(pair->openssl_name) == len && 0 == memcmp(cipher_name, pair->openssl_name, len))
            || (strlen(pair->iana_name) == len && 0 == memcmp(cipher_name, pair->iana_name, len)))
        {
            return pair;
        }
        pair++;
    }

    /* No entry found, return NULL */
    return NULL;
}