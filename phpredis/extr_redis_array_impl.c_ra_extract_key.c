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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int /*<<< orphan*/  z_fun; } ;
typedef  TYPE_1__ RedisArray ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ra_call_extractor (TYPE_1__*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/ * zend_string_init (char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *
ra_extract_key(RedisArray *ra, const char *key, int key_len)
{
    char *start, *end;

    if (Z_TYPE(ra->z_fun) != IS_NULL) {
        return ra_call_extractor(ra, key, key_len);
    } else if ((start = strchr(key, '{')) == NULL || (end = strchr(start + 1, '}')) == NULL) {
        return zend_string_init(key, key_len, 0);
    }
    /* found substring */
    return zend_string_init(start + 1, end - start - 1, 0);
}