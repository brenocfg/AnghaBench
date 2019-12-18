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
struct TYPE_3__ {int flags; scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int BIO_FLAGS_UPLINK_INTERNAL ; 
 int /*<<< orphan*/  UP_fgets (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static int file_gets(BIO *bp, char *buf, int size)
{
    int ret = 0;

    buf[0] = '\0';
    if (bp->flags & BIO_FLAGS_UPLINK_INTERNAL) {
        if (!UP_fgets(buf, size, bp->ptr))
            goto err;
    } else {
        if (!fgets(buf, size, (FILE *)bp->ptr))
            goto err;
    }
    if (buf[0] != '\0')
        ret = strlen(buf);
 err:
    return ret;
}