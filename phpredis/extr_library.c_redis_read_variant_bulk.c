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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_FALSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* redis_sock_read_bulk_reply (int /*<<< orphan*/ *,int) ; 

int
redis_read_variant_bulk(RedisSock *redis_sock, int size, zval *z_ret
                       )
{
    // Attempt to read the bulk reply
    char *bulk_resp = redis_sock_read_bulk_reply(redis_sock, size);

    /* Set our reply to FALSE on failure, and the string on success */
    if(bulk_resp == NULL) {
        ZVAL_FALSE(z_ret);
        return -1;
    }
    ZVAL_STRINGL(z_ret, bulk_resp, size);
    efree(bulk_resp);
    return 0;
}