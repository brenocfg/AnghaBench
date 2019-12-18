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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int PEM_FLAG_EAY_COMPATIBLE ; 
 int PEM_FLAG_SECURE ; 
 int pem_bytes_read_bio_flags (unsigned char**,long*,char**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 

int PEM_bytes_read_bio_secmem(unsigned char **pdata, long *plen, char **pnm,
                              const char *name, BIO *bp, pem_password_cb *cb,
                              void *u) {
    return pem_bytes_read_bio_flags(pdata, plen, pnm, name, bp, cb, u,
                                    PEM_FLAG_SECURE | PEM_FLAG_EAY_COMPATIBLE);
}