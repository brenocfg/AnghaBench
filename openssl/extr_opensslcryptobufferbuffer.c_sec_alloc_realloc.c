#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ BUF_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_secure_clear_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* OPENSSL_secure_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *sec_alloc_realloc(BUF_MEM *str, size_t len)
{
    char *ret;

    ret = OPENSSL_secure_malloc(len);
    if (str->data != NULL) {
        if (ret != NULL) {
            memcpy(ret, str->data, str->length);
            OPENSSL_secure_clear_free(str->data, str->length);
            str->data = NULL;
        }
    }
    return ret;
}