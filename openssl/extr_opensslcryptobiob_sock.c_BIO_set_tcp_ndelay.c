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

/* Variables and functions */

int BIO_set_tcp_ndelay(int s, int on)
{
    int ret = 0;
# if defined(TCP_NODELAY) && (defined(IPPROTO_TCP) || defined(SOL_TCP))
    int opt;

#  ifdef SOL_TCP
    opt = SOL_TCP;
#  else
#   ifdef IPPROTO_TCP
    opt = IPPROTO_TCP;
#   endif
#  endif

    ret = setsockopt(s, opt, TCP_NODELAY, (char *)&on, sizeof(on));
# endif
    return (ret == 0);
}