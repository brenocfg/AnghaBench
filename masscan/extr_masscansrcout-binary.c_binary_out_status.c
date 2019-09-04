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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned char Out_Arp2 ; 
 unsigned char Out_Closed2 ; 
 unsigned char Out_Open2 ; 
#define  PortStatus_Arp 130 
#define  PortStatus_Closed 129 
#define  PortStatus_Open 128 
 int /*<<< orphan*/  UNUSEDPARM (struct Output*) ; 
 int /*<<< orphan*/  exit (int) ; 
 size_t fwrite (unsigned char**,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void
binary_out_status(struct Output *out, FILE *fp, time_t timestamp,
    int status, unsigned ip, unsigned ip_proto, unsigned port, unsigned reason, unsigned ttl)
{
    unsigned char foo[256];
    size_t bytes_written;

    UNUSEDPARM(out);

    /* [TYPE] field */
    switch (status) {
    case PortStatus_Open:
        foo[0] = Out_Open2;
        break;
    case PortStatus_Closed:
        foo[0] = Out_Closed2;
        break;
    case PortStatus_Arp:
        foo[0] = Out_Arp2;
        break;
    default:
        return;
    }

    /* [LENGTH] field */
    foo[1] = 13;

    /* [TIMESTAMP] field */
    foo[2] = (unsigned char)(timestamp>>24);
    foo[3] = (unsigned char)(timestamp>>16);
    foo[4] = (unsigned char)(timestamp>> 8);
    foo[5] = (unsigned char)(timestamp>> 0);

    foo[6] = (unsigned char)(ip>>24);
    foo[7] = (unsigned char)(ip>>16);
    foo[8] = (unsigned char)(ip>> 8);
    foo[9] = (unsigned char)(ip>> 0);

    foo[10] = (unsigned char)(ip_proto);

    foo[11] = (unsigned char)(port>>8);
    foo[12] = (unsigned char)(port>>0);

    foo[13] = (unsigned char)reason;
    foo[14] = (unsigned char)ttl;



    bytes_written = fwrite(&foo, 1, 15, fp);
    if (bytes_written != 15) {
        perror("output");
        exit(1);
    }
    out->rotate.bytes_written += bytes_written;
}