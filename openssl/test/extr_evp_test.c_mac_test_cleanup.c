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
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  salt; int /*<<< orphan*/  custom; int /*<<< orphan*/  iv; int /*<<< orphan*/  key; int /*<<< orphan*/  alg; int /*<<< orphan*/  controls; int /*<<< orphan*/  mac_name; int /*<<< orphan*/  mac; } ;
typedef  TYPE_1__ MAC_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openssl_free ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mac_test_cleanup(EVP_TEST *t)
{
    MAC_DATA *mdat = t->data;

    EVP_MAC_free(mdat->mac);
    OPENSSL_free(mdat->mac_name);
    sk_OPENSSL_STRING_pop_free(mdat->controls, openssl_free);
    OPENSSL_free(mdat->alg);
    OPENSSL_free(mdat->key);
    OPENSSL_free(mdat->iv);
    OPENSSL_free(mdat->custom);
    OPENSSL_free(mdat->salt);
    OPENSSL_free(mdat->input);
    OPENSSL_free(mdat->output);
}