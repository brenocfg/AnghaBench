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
struct realm_password_file_t {int /*<<< orphan*/  entries; } ;
struct coro {int dummy; } ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 unsigned char* base64_decode (unsigned char*,size_t,size_t*) ; 
 scalar_t__ cache_coro_get_and_ref_entry (int /*<<< orphan*/ ,struct coro*,char const*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 char* hash_find (int /*<<< orphan*/ ,unsigned char*) ; 
 char* memchr (unsigned char*,char,size_t) ; 
 int /*<<< orphan*/  realm_password_cache ; 
 int streq (char*,char*) ; 

__attribute__((used)) static bool authorize(struct coro *coro,
                      const char *header,
                      size_t header_len,
                      const char *password_file)
{
    struct realm_password_file_t *rpf;
    unsigned char *decoded;
    char *colon;
    char *password;
    char *looked_password;
    size_t decoded_len;
    bool password_ok = false;

    rpf = (struct realm_password_file_t *)cache_coro_get_and_ref_entry(
        realm_password_cache, coro, password_file);
    if (UNLIKELY(!rpf))
        return false;

    decoded = base64_decode((unsigned char *)header, header_len, &decoded_len);
    if (UNLIKELY(!decoded))
        return false;

    colon = memchr(decoded, ':', decoded_len);
    if (UNLIKELY(!colon))
        goto out;

    *colon = '\0';
    password = colon + 1;

    looked_password = hash_find(rpf->entries, decoded);
    if (looked_password)
        password_ok = streq(password, looked_password);

out:
    free(decoded);
    return password_ok;
}