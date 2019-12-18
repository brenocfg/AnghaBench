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
struct key {int /*<<< orphan*/  member_0; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  server_key ;

/* Variables and functions */
 char* BPTR (struct buffer*) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_NONFATAL ; 
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  buf_clear (struct buffer*) ; 
 int /*<<< orphan*/  buf_set_read (struct buffer*,void*,int) ; 
 int /*<<< orphan*/  buffer_write_file (char const*,struct buffer*) ; 
 struct buffer clear_buf () ; 
 int /*<<< orphan*/  crypto_pem_encode (char const*,struct buffer*,struct buffer*,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rand_bytes (void*,int) ; 
 int /*<<< orphan*/  secure_memzero (struct key*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
write_pem_key_file(const char *filename, const char *pem_name)
{
    struct gc_arena gc = gc_new();
    struct key server_key = { 0 };
    struct buffer server_key_buf = clear_buf();
    struct buffer server_key_pem = clear_buf();

    if (!rand_bytes((void *)&server_key, sizeof(server_key)))
    {
        msg(M_NONFATAL, "ERROR: could not generate random key");
        goto cleanup;
    }
    buf_set_read(&server_key_buf, (void *)&server_key, sizeof(server_key));
    if (!crypto_pem_encode(pem_name, &server_key_pem,
                           &server_key_buf, &gc))
    {
        msg(M_WARN, "ERROR: could not PEM-encode key");
        goto cleanup;
    }

    if (!filename || strcmp(filename, "")==0)
    {
        printf("%s\n", BPTR(&server_key_pem));
    }
    else if (!buffer_write_file(filename, &server_key_pem))
    {
        msg(M_ERR, "ERROR: could not write key file");
        goto cleanup;
    }

cleanup:
    secure_memzero(&server_key, sizeof(server_key));
    buf_clear(&server_key_pem);
    gc_free(&gc);
    return;
}