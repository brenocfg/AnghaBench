#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  max_fragment_size; int /*<<< orphan*/  app_data_size; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;

/* Variables and functions */
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  default_app_data_size ; 
 int /*<<< orphan*/  default_max_fragment_size ; 

SSL_TEST_CTX *SSL_TEST_CTX_new(void)
{
    SSL_TEST_CTX *ret;

    /* The return code is checked by caller */
    if ((ret = OPENSSL_zalloc(sizeof(*ret))) != NULL) {
        ret->app_data_size = default_app_data_size;
        ret->max_fragment_size = default_max_fragment_size;
    }
    return ret;
}