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
struct lwan_response_settings {int code; } ;
struct hash {int dummy; } ;
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */
 char* hash_find (struct hash const*,char*) ; 
 int /*<<< orphan*/  lwan_status_error (char*,...) ; 
 int /*<<< orphan*/  parse_int (char const*,int) ; 
 void* response_create (char const*,struct lwan_response_settings*) ; 

__attribute__((used)) static void *response_create_from_hash(const char *prefix,
                                       const struct hash *hash)
{
    const char *code = hash_find(hash, "code");

    if (!code) {
        lwan_status_error("`code` not supplied");
        return NULL;
    }

    struct lwan_response_settings settings = {
        .code = (enum lwan_http_status)parse_int(code, 999)
    };

    if (settings.code == 999) {
        lwan_status_error("Unknown error code: %s", code);
        return NULL;
    }

    return response_create(prefix, &settings);
}