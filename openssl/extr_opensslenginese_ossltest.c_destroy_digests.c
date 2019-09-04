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
 int /*<<< orphan*/  EVP_MD_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _hidden_md5_md ; 
 int /*<<< orphan*/ * _hidden_sha1_md ; 
 int /*<<< orphan*/ * _hidden_sha256_md ; 
 int /*<<< orphan*/ * _hidden_sha384_md ; 
 int /*<<< orphan*/ * _hidden_sha512_md ; 

__attribute__((used)) static void destroy_digests(void)
{
    EVP_MD_meth_free(_hidden_md5_md);
    _hidden_md5_md = NULL;
    EVP_MD_meth_free(_hidden_sha1_md);
    _hidden_sha1_md = NULL;
    EVP_MD_meth_free(_hidden_sha256_md);
    _hidden_sha256_md = NULL;
    EVP_MD_meth_free(_hidden_sha384_md);
    _hidden_sha384_md = NULL;
    EVP_MD_meth_free(_hidden_sha512_md);
    _hidden_sha512_md = NULL;
}