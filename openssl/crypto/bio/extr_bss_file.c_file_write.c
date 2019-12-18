#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; scalar_t__ ptr; scalar_t__ init; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int BIO_FLAGS_UPLINK_INTERNAL ; 
 int UP_fwrite (char const*,int,int,scalar_t__) ; 
 int fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int file_write(BIO *b, const char *in, int inl)
{
    int ret = 0;

    if (b->init && (in != NULL)) {
        if (b->flags & BIO_FLAGS_UPLINK_INTERNAL)
            ret = UP_fwrite(in, (int)inl, 1, b->ptr);
        else
            ret = fwrite(in, (int)inl, 1, (FILE *)b->ptr);
        if (ret)
            ret = inl;
        /* ret=fwrite(in,1,(int)inl,(FILE *)b->ptr); */
        /*
         * according to Tim Hudson <tjh@openssl.org>, the commented out
         * version above can cause 'inl' write calls under some stupid stdio
         * implementations (VMS)
         */
    }
    return ret;
}