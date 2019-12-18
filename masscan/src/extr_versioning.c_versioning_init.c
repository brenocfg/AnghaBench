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
struct Banner1 {void* http_fields; } ;

/* Variables and functions */

__attribute__((used)) static void *
versioning_init(struct Banner1 *b)
{
    //b->memcached_responses = smack_create("memcached-responses", SMACK_CASE_INSENSITIVE);
    
    return b->http_fields;
}