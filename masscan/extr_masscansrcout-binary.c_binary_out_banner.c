#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_2__ {size_t bytes_written; } ;
struct Output {TYPE_1__ rotate; } ;
typedef  enum ApplicationProtocol { ____Placeholder_ApplicationProtocol } ApplicationProtocol ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned char Out_Banner9 ; 
 int /*<<< orphan*/  UNUSEDPARM (struct Output*) ; 
 int /*<<< orphan*/  exit (int) ; 
 size_t fwrite (unsigned char**,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void
binary_out_banner(struct Output *out, FILE *fp, time_t timestamp,
        unsigned ip, unsigned ip_proto, unsigned port,
        enum ApplicationProtocol proto, unsigned ttl,
        const unsigned char *px, unsigned length)
{
    unsigned char foo[32768];
    unsigned i;
    size_t bytes_written;
    static const unsigned HeaderLength = 14;

    UNUSEDPARM(out);

    /* [TYPE] field */
    foo[0] = Out_Banner9; /*banner*/

    /* [LENGTH] field*/
    if (length >= 128 * 128 - HeaderLength)
        return;
    if (length < 128 - HeaderLength) {
        foo[1] = (unsigned char)(length + HeaderLength);
        i = 2;
    } else {
        foo[1] = (unsigned char)((length + HeaderLength)>>7) | 0x80;
        foo[2] = (unsigned char)((length + HeaderLength) & 0x7F);
        i = 3;
    }

    /* [TIMESTAMP] field */
    foo[i+0] = (unsigned char)(timestamp>>24);
    foo[i+1] = (unsigned char)(timestamp>>16);
    foo[i+2] = (unsigned char)(timestamp>> 8);
    foo[i+3] = (unsigned char)(timestamp>> 0);

    foo[i+4] = (unsigned char)(ip>>24);
    foo[i+5] = (unsigned char)(ip>>16);
    foo[i+6] = (unsigned char)(ip>> 8);
    foo[i+7] = (unsigned char)(ip>> 0);

    foo[i+8] = (unsigned char)(ip_proto);

    foo[i+ 9] = (unsigned char)(port>>8);
    foo[i+10] = (unsigned char)(port>>0);

    foo[i+11] = (unsigned char)(proto>>8);
    foo[i+12] = (unsigned char)(proto>>0);

    foo[i+13] = (unsigned char)(ttl);

    /* Banner */
    memcpy(foo+i+14, px, length);


    bytes_written = fwrite(&foo, 1, length+i+HeaderLength, fp);
    if (bytes_written != length+i+HeaderLength) {
        perror("output");
        exit(1);
    }
    out->rotate.bytes_written += bytes_written;
}