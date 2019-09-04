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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_write_ex (int /*<<< orphan*/ *,unsigned char*,size_t,size_t*) ; 
 int SSL3_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_record(BIO *b, size_t len, int rectype, int recversion)
{
    unsigned char header[SSL3_RT_HEADER_LENGTH];
    size_t written;
    unsigned char buf[256];

    memset(buf, 0, sizeof(buf));

    header[0] = rectype;
    header[1] = (recversion >> 8) & 0xff;
    header[2] = recversion & 0xff;
    header[3] = (len >> 8) & 0xff;
    header[4] = len & 0xff;

    if (!BIO_write_ex(b, header, SSL3_RT_HEADER_LENGTH, &written)
            || written != SSL3_RT_HEADER_LENGTH)
        return 0;

    while (len > 0) {
        size_t outlen;

        if (len > sizeof(buf))
            outlen = sizeof(buf);
        else
            outlen = len;

        if (!BIO_write_ex(b, buf, outlen, &written)
                || written != outlen)
            return 0;

        len -= outlen;
    }

    return 1;
}