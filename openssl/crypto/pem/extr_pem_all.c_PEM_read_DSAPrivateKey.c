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
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  DSA ;

/* Variables and functions */
 int /*<<< orphan*/ * PEM_read_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * pkey_get_dsa (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

DSA *PEM_read_DSAPrivateKey(FILE *fp, DSA **dsa, pem_password_cb *cb, void *u)
{
    EVP_PKEY *pktmp;
    pktmp = PEM_read_PrivateKey(fp, NULL, cb, u);
    return pkey_get_dsa(pktmp, dsa); /* will free pktmp */
}