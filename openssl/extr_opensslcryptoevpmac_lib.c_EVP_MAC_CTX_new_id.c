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
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_MAC_CTX_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_macbynid (int) ; 

EVP_MAC_CTX *EVP_MAC_CTX_new_id(int id)
{
    const EVP_MAC *mac = EVP_get_macbynid(id);

    if (mac == NULL)
        return NULL;
    return EVP_MAC_CTX_new(mac);
}