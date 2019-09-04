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
struct TYPE_4__ {int /*<<< orphan*/  key; int /*<<< orphan*/  salt; int /*<<< orphan*/  pass; } ;
typedef  TYPE_1__ PBE_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pbe_test_cleanup(EVP_TEST *t)
{
    PBE_DATA *pdat = t->data;

    OPENSSL_free(pdat->pass);
    OPENSSL_free(pdat->salt);
    OPENSSL_free(pdat->key);
}