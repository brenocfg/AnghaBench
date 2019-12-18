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
typedef  int /*<<< orphan*/  OSSL_NAMEMAP ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_get_cipherbyname (char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_int_ne (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_ptr_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int ossl_namemap_add (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * ossl_namemap_stored (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_cipherbyname(void)
{
    int id;
    OSSL_NAMEMAP *nm = ossl_namemap_stored(NULL);
    const EVP_CIPHER *aes128, *bar;

    id = ossl_namemap_add(nm, 0, "AES-128-CBC");
    if (!TEST_int_ne(id, 0))
        return 0;
    if (!TEST_int_eq(ossl_namemap_add(nm, id, "bar"), id))
        return 0;

    aes128 = EVP_get_cipherbyname("AES-128-CBC");
    if (!TEST_ptr(aes128))
        return 0;
    bar = EVP_get_cipherbyname("bar");
    if (!TEST_ptr_eq(aes128, bar))
        return 0;

    return 1;
}