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
struct TYPE_3__ {scalar_t__ bai_protocol; int bai_socktype; } ;
typedef  TYPE_1__ BIO_ADDRINFO ;

/* Variables and functions */
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 

int BIO_ADDRINFO_protocol(const BIO_ADDRINFO *bai)
{
    if (bai != NULL) {
        if (bai->bai_protocol != 0)
            return bai->bai_protocol;

#ifdef AF_UNIX
        if (bai->bai_family == AF_UNIX)
            return 0;
#endif

        switch (bai->bai_socktype) {
        case SOCK_STREAM:
            return IPPROTO_TCP;
        case SOCK_DGRAM:
            return IPPROTO_UDP;
        default:
            break;
        }
    }
    return 0;
}