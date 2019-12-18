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
typedef  int REDIS_REPLY_TYPE ;

/* Variables and functions */
 int FAILURE ; 
#define  TYPE_BULK 132 
#define  TYPE_ERR 131 
#define  TYPE_INT 130 
#define  TYPE_LINE 129 
#define  TYPE_MULTIBULK 128 
 int /*<<< orphan*/  add_next_index_long (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redis_exception_ce ; 
 scalar_t__ redis_read_reply_type (int /*<<< orphan*/ *,int*,long*) ; 
 int /*<<< orphan*/  redis_read_variant_bulk (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redis_read_variant_line (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
redis_read_multibulk_recursive(RedisSock *redis_sock, int elements, int status_strings,
                               zval *z_ret)
{
    long reply_info;
    REDIS_REPLY_TYPE reply_type;
    zval z_subelem;

    // Iterate while we have elements
    while(elements > 0) {
        // Attempt to read our reply type
        if(redis_read_reply_type(redis_sock, &reply_type, &reply_info
                                ) < 0)
        {
            zend_throw_exception_ex(redis_exception_ce, 0,
                "protocol error, couldn't parse MULTI-BULK response\n");
            return FAILURE;
        }

        // Switch on our reply-type byte
        switch(reply_type) {
            case TYPE_ERR:
            case TYPE_LINE:
                redis_read_variant_line(redis_sock, reply_type, status_strings,
                                        &z_subelem);
                add_next_index_zval(z_ret, &z_subelem);
                break;
            case TYPE_INT:
                // Add our long value
                add_next_index_long(z_ret, reply_info);
                break;
            case TYPE_BULK:
                // Init a zval for our bulk response, read and add it
                redis_read_variant_bulk(redis_sock, reply_info, &z_subelem);
                add_next_index_zval(z_ret, &z_subelem);
                break;
            case TYPE_MULTIBULK:
                // Construct an array for our sub element, and add it, and recurse
                array_init(&z_subelem);
                add_next_index_zval(z_ret, &z_subelem);
                redis_read_multibulk_recursive(redis_sock, reply_info, status_strings,
                                               &z_subelem);
                break;
            default:
                // Stop the compiler from whinging
                break;
        }

        /* Decrement our element counter */
        elements--;
    }

    return 0;
}