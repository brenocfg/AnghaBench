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
#define  EACCES 172 
#define  EADDRINUSE 171 
#define  EADDRNOTAVAIL 170 
#define  EAFNOSUPPORT 169 
#define  EALREADY 168 
#define  EBADF 167 
#define  ECONNABORTED 166 
#define  ECONNREFUSED 165 
#define  ECONNRESET 164 
#define  EDESTADDRREQ 163 
#define  EDQUOT 162 
#define  EFAULT 161 
#define  EHOSTDOWN 160 
#define  EHOSTUNREACH 159 
#define  EINPROGRESS 158 
#define  EINTR 157 
#define  EINVAL 156 
#define  EISCONN 155 
#define  ELOOP 154 
#define  EMFILE 153 
#define  EMSGSIZE 152 
#define  ENAMETOOLONG 151 
#define  ENETDOWN 150 
#define  ENETRESET 149 
#define  ENETUNREACH 148 
#define  ENOBUFS 147 
#define  ENOPROTOOPT 146 
#define  ENOTCONN 145 
#define  ENOTEMPTY 144 
#define  ENOTSOCK 143 
#define  EOPNOTSUPP 142 
#define  EPERM 141 
#define  EPFNOSUPPORT 140 
#define  EPIPE 139 
#define  EPROCLIM 138 
#define  EPROTONOSUPPORT 137 
#define  EPROTOTYPE 136 
#define  EREMOTE 135 
#define  ESHUTDOWN 134 
#define  ESOCKTNOSUPPORT 133 
#define  ESTALE 132 
#define  ETIMEDOUT 131 
#define  ETOOMANYREFS 130 
#define  EUSERS 129 
#define  EWOULDBLOCK 128 
 int WSAEACCES ; 
 int WSAEADDRINUSE ; 
 int WSAEADDRNOTAVAIL ; 
 int WSAEAFNOSUPPORT ; 
 int WSAEALREADY ; 
 int WSAEBADF ; 
 int WSAECONNABORTED ; 
 int WSAECONNREFUSED ; 
 int WSAECONNRESET ; 
 int WSAEDESTADDRREQ ; 
 int WSAEDQUOT ; 
 int WSAEFAULT ; 
 int WSAEHOSTDOWN ; 
 int WSAEHOSTUNREACH ; 
 int WSAEINPROGRESS ; 
 int WSAEINTR ; 
 int WSAEINVAL ; 
 int WSAEISCONN ; 
 int WSAELOOP ; 
 int WSAEMFILE ; 
 int WSAEMSGSIZE ; 
 int WSAENAMETOOLONG ; 
 int WSAENETDOWN ; 
 int WSAENETRESET ; 
 int WSAENETUNREACH ; 
 int WSAENOBUFS ; 
 int WSAENOPROTOOPT ; 
 int WSAENOTCONN ; 
 int WSAENOTEMPTY ; 
 int WSAENOTSOCK ; 
 int WSAEOPNOTSUPP ; 
 int WSAEPFNOSUPPORT ; 
 int WSAEPROCLIM ; 
 int WSAEPROTONOSUPPORT ; 
 int WSAEPROTOTYPE ; 
 int WSAEREMOTE ; 
 int WSAESHUTDOWN ; 
 int WSAESOCKTNOSUPPORT ; 
 int WSAESTALE ; 
 int WSAETIMEDOUT ; 
 int WSAETOOMANYREFS ; 
 int WSAEUSERS ; 
 int WSAEWOULDBLOCK ; 
 int errno ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int sock_get_error( int err )
{
#if !defined(__MINGW32__) && !defined (_MSC_VER)
    switch (err)
    {
        case EINTR:             return WSAEINTR;
        case EBADF:             return WSAEBADF;
        case EPERM:
        case EACCES:            return WSAEACCES;
        case EFAULT:            return WSAEFAULT;
        case EINVAL:            return WSAEINVAL;
        case EMFILE:            return WSAEMFILE;
        case EWOULDBLOCK:       return WSAEWOULDBLOCK;
        case EINPROGRESS:       return WSAEINPROGRESS;
        case EALREADY:          return WSAEALREADY;
        case ENOTSOCK:          return WSAENOTSOCK;
        case EDESTADDRREQ:      return WSAEDESTADDRREQ;
        case EMSGSIZE:          return WSAEMSGSIZE;
        case EPROTOTYPE:        return WSAEPROTOTYPE;
        case ENOPROTOOPT:       return WSAENOPROTOOPT;
        case EPROTONOSUPPORT:   return WSAEPROTONOSUPPORT;
        case ESOCKTNOSUPPORT:   return WSAESOCKTNOSUPPORT;
        case EOPNOTSUPP:        return WSAEOPNOTSUPP;
        case EPFNOSUPPORT:      return WSAEPFNOSUPPORT;
        case EAFNOSUPPORT:      return WSAEAFNOSUPPORT;
        case EADDRINUSE:        return WSAEADDRINUSE;
        case EADDRNOTAVAIL:     return WSAEADDRNOTAVAIL;
        case ENETDOWN:          return WSAENETDOWN;
        case ENETUNREACH:       return WSAENETUNREACH;
        case ENETRESET:         return WSAENETRESET;
        case ECONNABORTED:      return WSAECONNABORTED;
        case EPIPE:
        case ECONNRESET:        return WSAECONNRESET;
        case ENOBUFS:           return WSAENOBUFS;
        case EISCONN:           return WSAEISCONN;
        case ENOTCONN:          return WSAENOTCONN;
        case ESHUTDOWN:         return WSAESHUTDOWN;
        case ETOOMANYREFS:      return WSAETOOMANYREFS;
        case ETIMEDOUT:         return WSAETIMEDOUT;
        case ECONNREFUSED:      return WSAECONNREFUSED;
        case ELOOP:             return WSAELOOP;
        case ENAMETOOLONG:      return WSAENAMETOOLONG;
        case EHOSTDOWN:         return WSAEHOSTDOWN;
        case EHOSTUNREACH:      return WSAEHOSTUNREACH;
        case ENOTEMPTY:         return WSAENOTEMPTY;
#ifdef EPROCLIM
        case EPROCLIM:          return WSAEPROCLIM;
#endif
#ifdef EUSERS
        case EUSERS:            return WSAEUSERS;
#endif
#ifdef EDQUOT
        case EDQUOT:            return WSAEDQUOT;
#endif
#ifdef ESTALE
        case ESTALE:            return WSAESTALE;
#endif
#ifdef EREMOTE
        case EREMOTE:           return WSAEREMOTE;
#endif
    default: errno = err; perror( "sock_set_error" ); return WSAEFAULT;
    }
#endif
    return err;
}