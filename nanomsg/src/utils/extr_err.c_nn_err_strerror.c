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
#define  EACCES 156 
#define  EADDRINUSE 155 
#define  EADDRNOTAVAIL 154 
#define  EAFNOSUPPORT 153 
#define  EAGAIN 152 
#define  EBADF 151 
#define  ECONNABORTED 150 
#define  ECONNREFUSED 149 
#define  ECONNRESET 148 
#define  EFAULT 147 
#define  EFSM 146 
#define  EHOSTUNREACH 145 
#define  EINPROGRESS 144 
#define  EINVAL 143 
#define  EISCONN 142 
#define  EMFILE 141 
#define  EMSGSIZE 140 
#define  ENETDOWN 139 
#define  ENETRESET 138 
#define  ENETUNREACH 137 
#define  ENOBUFS 136 
#define  ENOPROTOOPT 135 
#define  ENOTCONN 134 
#define  ENOTSOCK 133 
#define  ENOTSUP 132 
#define  EPROTO 131 
#define  EPROTONOSUPPORT 130 
#define  ETERM 129 
#define  ETIMEDOUT 128 
 char const* strerror (int) ; 

const char *nn_err_strerror (int errnum)
{
    switch (errnum) {
#if defined NN_HAVE_WINDOWS
    case ENOTSUP:
        return "Not supported";
    case EPROTONOSUPPORT:
        return "Protocol not supported";
    case ENOBUFS:
        return "No buffer space available";
    case ENETDOWN:
        return "Network is down";
    case EADDRINUSE:
        return "Address in use";
    case EADDRNOTAVAIL:
        return "Address not available";
    case ECONNREFUSED:
        return "Connection refused";
    case EINPROGRESS:
        return "Operation in progress";
    case ENOTSOCK:
        return "Not a socket";
    case EAFNOSUPPORT:
        return "Address family not supported";
    case EPROTO:
        return "Protocol error";
    case EAGAIN:
        return "Resource unavailable, try again";
    case EBADF:
        return "Bad file descriptor";
    case EINVAL:
        return "Invalid argument";
    case EMFILE:
        return "Too many open files";
    case EFAULT:
        return "Bad address";
    case EACCES:
        return "Permission denied";
    case ENETRESET:
        return "Connection aborted by network";
    case ENETUNREACH:
        return "Network unreachable";
    case EHOSTUNREACH:
        return "Host is unreachable";
    case ENOTCONN:
        return "The socket is not connected";
    case EMSGSIZE:
        return "Message too large";
    case ETIMEDOUT:
        return "Timed out";
    case ECONNABORTED:
        return "Connection aborted";
    case ECONNRESET:
        return "Connection reset";
    case ENOPROTOOPT:
        return "Protocol not available";
    case EISCONN:
        return "Socket is connected";
#endif
    case ETERM:
        return "Nanomsg library was terminated";
    case EFSM:
        return "Operation cannot be performed in this state";
    default:
#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable:4996)
#endif
        return strerror (errnum);
#if defined _MSC_VER
#pragma warning (pop)
#endif
    }
}