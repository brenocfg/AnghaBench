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
typedef  int /*<<< orphan*/  tid ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  CRYPTO_THREAD_ID ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,char*,char const*,char const*,char const*,char const*,int,char const*) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 
 int ERR_TXT_STRING ; 
 unsigned long ERR_get_error_all (char const**,int*,char const**,char const**,int*) ; 
 char* ERR_lib_error_string (unsigned long) ; 
 char* ERR_reason_error_string (unsigned long) ; 
 char* OPENSSL_buf2hexstr (unsigned char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 size_t strlen (char*) ; 

void ERR_print_errors_cb(int (*cb) (const char *str, size_t len, void *u),
                         void *u)
{
    CRYPTO_THREAD_ID tid = CRYPTO_THREAD_get_current_id();
    unsigned long l;
    char buf[4096], *hex;
    const char *lib, *reason;
    const char *file, *data, *func;
    int line, flags;

    while ((l = ERR_get_error_all(&file, &line, &func, &data, &flags)) != 0) {
        lib = ERR_lib_error_string(l);
        reason = ERR_reason_error_string(l);
        if (func == NULL)
            func = "unknown function";
        if ((flags & ERR_TXT_STRING) == 0)
            data = "";
        hex = OPENSSL_buf2hexstr((const unsigned char *)&tid, sizeof(tid));
        BIO_snprintf(buf, sizeof(buf), "%s:error:%s:%s:%s:%s:%d:%s\n",
                     hex, lib, func, reason, file, line, data);
        OPENSSL_free(hex);
        if (cb(buf, strlen(buf), u) <= 0)
            break;              /* abort outputting the error report */
    }
}