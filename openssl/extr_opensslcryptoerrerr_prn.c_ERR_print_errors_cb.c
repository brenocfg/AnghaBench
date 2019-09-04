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
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  CRYPTO_THREAD_ID ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,unsigned long,char*,char const*,int,char const*) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 
 int ERR_TXT_STRING ; 
 int /*<<< orphan*/  ERR_error_string_n (unsigned long,char*,int) ; 
 unsigned long ERR_get_error_line_data (char const**,int*,char const**,int*) ; 
 size_t strlen (char*) ; 

void ERR_print_errors_cb(int (*cb) (const char *str, size_t len, void *u),
                         void *u)
{
    unsigned long l;
    char buf[256];
    char buf2[4096];
    const char *file, *data;
    int line, flags;
    /*
     * We don't know what kind of thing CRYPTO_THREAD_ID is. Here is our best
     * attempt to convert it into something we can print.
     */
    union {
        CRYPTO_THREAD_ID tid;
        unsigned long ltid;
    } tid;

    tid.ltid = 0;
    tid.tid = CRYPTO_THREAD_get_current_id();

    while ((l = ERR_get_error_line_data(&file, &line, &data, &flags)) != 0) {
        ERR_error_string_n(l, buf, sizeof(buf));
        BIO_snprintf(buf2, sizeof(buf2), "%lu:%s:%s:%d:%s\n", tid.ltid, buf,
                     file, line, (flags & ERR_TXT_STRING) ? data : "");
        if (cb(buf2, strlen(buf2), u) <= 0)
            break;              /* abort outputting the error report */
    }
}