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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_nid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_cipherbyname (char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strndup (char const*,int) ; 
 size_t find_cipher_data_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cryptodev_select_cipher_cb(const char *str, int len, void *usr)
{
    int *cipher_list = (int *)usr;
    char *name;
    const EVP_CIPHER *EVP;
    size_t i;

    if (len == 0)
        return 1;
    if (usr == NULL || (name = OPENSSL_strndup(str, len)) == NULL)
        return 0;
    EVP = EVP_get_cipherbyname(name);
    if (EVP == NULL)
        fprintf(stderr, "devcrypto: unknown cipher %s\n", name);
    else if ((i = find_cipher_data_index(EVP_CIPHER_nid(EVP))) != (size_t)-1)
        cipher_list[i] = 1;
    else
        fprintf(stderr, "devcrypto: cipher %s not available\n", name);
    OPENSSL_free(name);
    return 1;
}