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
struct lwan_redirect_settings {int /*<<< orphan*/  code; int /*<<< orphan*/  to; } ;
struct hash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_MOVED_PERMANENTLY ; 
 int /*<<< orphan*/  hash_find (struct hash const*,char*) ; 
 int /*<<< orphan*/  parse_http_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* redirect_create (char const*,struct lwan_redirect_settings*) ; 

__attribute__((used)) static void *redirect_create_from_hash(const char *prefix,
                                       const struct hash *hash)
{
    struct lwan_redirect_settings settings = {
        .to = hash_find(hash, "to"),
        .code =
            parse_http_code(hash_find(hash, "code"), HTTP_MOVED_PERMANENTLY),
    };

    return redirect_create(prefix, &settings);
}