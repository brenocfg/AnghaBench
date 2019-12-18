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
#define  EAGAIN 134 
#define  EALREADY 133 
#define  EINPROGRESS 132 
#define  EINTR 131 
#define  ENOTCONN 130 
#define  EPROTO 129 
#define  EWOULDBLOCK 128 

int BIO_fd_non_fatal_error(int err)
{
    switch (err) {

# ifdef EWOULDBLOCK
#  ifdef WSAEWOULDBLOCK
#   if WSAEWOULDBLOCK != EWOULDBLOCK
    case EWOULDBLOCK:
#   endif
#  else
    case EWOULDBLOCK:
#  endif
# endif

# if defined(ENOTCONN)
    case ENOTCONN:
# endif

# ifdef EINTR
    case EINTR:
# endif

# ifdef EAGAIN
#  if EWOULDBLOCK != EAGAIN
    case EAGAIN:
#  endif
# endif

# ifdef EPROTO
    case EPROTO:
# endif

# ifdef EINPROGRESS
    case EINPROGRESS:
# endif

# ifdef EALREADY
    case EALREADY:
# endif
        return 1;
    default:
        break;
    }
    return 0;
}