#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_5__ {TYPE_3__ sa; } ;
struct TYPE_6__ {TYPE_1__ addr; } ;
struct link_socket_actual {TYPE_2__ dest; } ;
typedef  int socklen_t ;
typedef  int socket_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct link_socket_actual) ; 
 int D_LINK_ERRORS ; 
 int M_ERRNO ; 
 int /*<<< orphan*/  M_WARN ; 
 int SOCKET_UNDEFINED ; 
 int accept (int,TYPE_3__*,int*) ; 
 int af_addr_size (int /*<<< orphan*/ ) ; 
 int getpeername (int,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int /*<<< orphan*/  openvpn_close_socket (int) ; 
 int /*<<< orphan*/  set_cloexec (int) ; 
 int /*<<< orphan*/  socket_defined (int) ; 

socket_descriptor_t
socket_do_accept(socket_descriptor_t sd,
                 struct link_socket_actual *act,
                 const bool nowait)
{
    /* af_addr_size WILL return 0 in this case if AFs other than AF_INET
     * are compiled because act is empty here.
     * could use getsockname() to support later remote_len check
     */
    socklen_t remote_len_af = af_addr_size(act->dest.addr.sa.sa_family);
    socklen_t remote_len = sizeof(act->dest.addr);
    socket_descriptor_t new_sd = SOCKET_UNDEFINED;

    CLEAR(*act);

#ifdef HAVE_GETPEERNAME
    if (nowait)
    {
        new_sd = getpeername(sd, &act->dest.addr.sa, &remote_len);

        if (!socket_defined(new_sd))
        {
            msg(D_LINK_ERRORS | M_ERRNO, "TCP: getpeername() failed");
        }
        else
        {
            new_sd = sd;
        }
    }
#else  /* ifdef HAVE_GETPEERNAME */
    if (nowait)
    {
        msg(M_WARN, "TCP: this OS does not provide the getpeername() function");
    }
#endif
    else
    {
        new_sd = accept(sd, &act->dest.addr.sa, &remote_len);
    }

#if 0 /* For debugging only, test the effect of accept() failures */
    {
        static int foo = 0;
        ++foo;
        if (foo & 1)
        {
            new_sd = -1;
        }
    }
#endif

    if (!socket_defined(new_sd))
    {
        msg(D_LINK_ERRORS | M_ERRNO, "TCP: accept(%d) failed", (int)sd);
    }
    /* only valid if we have remote_len_af!=0 */
    else if (remote_len_af && remote_len != remote_len_af)
    {
        msg(D_LINK_ERRORS, "TCP: Received strange incoming connection with unknown address length=%d", remote_len);
        openvpn_close_socket(new_sd);
        new_sd = SOCKET_UNDEFINED;
    }
    else
    {
        /* set socket file descriptor to not pass across execs, so that
         * scripts don't have access to it */
        set_cloexec(sd);
    }
    return new_sd;
}