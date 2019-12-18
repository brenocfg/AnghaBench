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
typedef  int /*<<< orphan*/  PROV_DH_CTX ;

/* Variables and functions */
 void* OPENSSL_zalloc (int) ; 

__attribute__((used)) static void *dh_newctx(void *provctx)
{
    return OPENSSL_zalloc(sizeof(PROV_DH_CTX));
}