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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  SALT_SIZE ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
digest(const void *p, int len, const char *password,
    const unsigned char *salt, unsigned char *md)
{
    EVP_MD_CTX ctx;
    unsigned int rlen;

    EVP_DigestInit(&ctx, EVP_sha1());
    EVP_DigestUpdate(&ctx, salt, SALT_SIZE);
    EVP_DigestUpdate(&ctx, password, strlen(password));
    EVP_DigestUpdate(&ctx, p, len);
    EVP_DigestFinal(&ctx, md, &rlen);
}