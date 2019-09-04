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
struct TYPE_4__ {struct TYPE_4__* buf; } ;
typedef  TYPE_1__ EVP_TEST_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void evp_test_buffer_free(EVP_TEST_BUFFER *db)
{
    if (db != NULL) {
        OPENSSL_free(db->buf);
        OPENSSL_free(db);
    }
}