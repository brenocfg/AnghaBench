#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 size_t OSSL_NELEM (TYPE_2__*) ; 
 TYPE_2__* cipher_data ; 
 TYPE_1__* cipher_driver_info ; 
 int /*<<< orphan*/  destroy_cipher_method (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_all_cipher_methods(void)
{
    size_t i;

    for (i = 0; i < OSSL_NELEM(cipher_data); i++) {
        destroy_cipher_method(cipher_data[i].nid);
        OPENSSL_free(cipher_driver_info[i].driver_name);
        cipher_driver_info[i].driver_name = NULL;
    }
}