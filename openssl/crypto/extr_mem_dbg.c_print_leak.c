#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tm {char* tm_hour; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {char* order; size_t array_siz; int /*<<< orphan*/  array; int /*<<< orphan*/  num; int /*<<< orphan*/  addr; int /*<<< orphan*/  threadid; int /*<<< orphan*/  line; int /*<<< orphan*/  file; int /*<<< orphan*/  time; } ;
struct TYPE_5__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  chunks; int /*<<< orphan*/  print_cb_arg; int /*<<< orphan*/  (* print_cb ) (char*,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ MEM_LEAK ;
typedef  TYPE_2__ MEM ;

/* Variables and functions */
 int BIO_snprintf (char*,size_t,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* OPENSSL_buf2hexstr (unsigned char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char** backtrace_symbols (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char**) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_leak(const MEM *m, MEM_LEAK *l)
{
    char buf[1024];
    char *bufp = buf, *hex;
    size_t len = sizeof(buf);
    int n;
    struct tm *lcl = NULL;

    lcl = localtime(&m->time);
    n = BIO_snprintf(bufp, len, "[%02d:%02d:%02d] ",
                     lcl->tm_hour, lcl->tm_min, lcl->tm_sec);
    if (n <= 0) {
        bufp[0] = '\0';
        return;
    }
    bufp += n;
    len -= n;

    n = BIO_snprintf(bufp, len, "%5lu file=%s, line=%d, ",
                     m->order, m->file, m->line);
    if (n <= 0)
        return;
    bufp += n;
    len -= n;

    hex = OPENSSL_buf2hexstr((const unsigned char *)&m->threadid,
                             sizeof(m->threadid));
    n = BIO_snprintf(bufp, len, "thread=%s, number=%d, address=%p\n", hex,
                     m->num, m->addr);
    OPENSSL_free(hex);
    if (n <= 0)
        return;
    bufp += n;
    len -= n;

    l->print_cb(buf, (size_t)(bufp - buf), l->print_cb_arg);
    l->chunks++;
    l->bytes += m->num;

#ifndef OPENSSL_NO_CRYPTO_MDEBUG_BACKTRACE
    {
        size_t i;
        char **strings = backtrace_symbols(m->array, m->array_siz);

        for (i = 0; i < m->array_siz; i++)
            fprintf(stderr, "##> %s\n", strings[i]);
        free(strings);
    }
#endif
}