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
 int /*<<< orphan*/  CERT_STORE_READONLY_FLAG ; 
 int /*<<< orphan*/  CRYPT_InitStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EmptyStoreVtbl ; 
 int /*<<< orphan*/  StoreTypeEmpty ; 
 int /*<<< orphan*/  empty_store ; 

void init_empty_store(void)
{
    CRYPT_InitStore(&empty_store, CERT_STORE_READONLY_FLAG, StoreTypeEmpty, &EmptyStoreVtbl);
}