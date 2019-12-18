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
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EADDRINUSE ; 
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EHOSTUNREACH ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EISCONN ; 
 int /*<<< orphan*/  EMFILE ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  ENOTSOCK ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  EPROTONOSUPPORT ; 
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int /*<<< orphan*/  NOTICE ; 
#define  WSAEACCES 161 
#define  WSAEADDRINUSE 160 
#define  WSAEADDRNOTAVAIL 159 
#define  WSAEAFNOSUPPORT 158 
#define  WSAECONNABORTED 157 
#define  WSAECONNREFUSED 156 
#define  WSAECONNRESET 155 
#define  WSAEDESTADDRREQ 154 
#define  WSAEDISCON 153 
#define  WSAEFAULT 152 
#define  WSAEHOSTDOWN 151 
#define  WSAEHOSTUNREACH 150 
#define  WSAEINPROGRESS 149 
#define  WSAEINTR 148 
#define  WSAEINVAL 147 
#define  WSAEINVALIDPROCTABLE 146 
#define  WSAEINVALIDPROVIDER 145 
#define  WSAEISCONN 144 
#define  WSAEMFILE 143 
#define  WSAEMSGSIZE 142 
#define  WSAENETDOWN 141 
#define  WSAENETRESET 140 
#define  WSAENETUNREACH 139 
#define  WSAENOBUFS 138 
#define  WSAENOTCONN 137 
#define  WSAENOTSOCK 136 
#define  WSAEOPNOTSUPP 135 
#define  WSAEPROTONOSUPPORT 134 
#define  WSAEPROTOTYPE 133 
#define  WSAESHUTDOWN 132 
#define  WSAESOCKTNOSUPPORT 131 
#define  WSAEWOULDBLOCK 130 
 int WSAGetLastError () ; 
#define  WSAHOST_NOT_FOUND 129 
#define  WSANOTINITIALISED 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static void
TranslateSocketError(void)
{
	switch (WSAGetLastError())
	{
		case WSAEINVAL:
		case WSANOTINITIALISED:
		case WSAEINVALIDPROVIDER:
		case WSAEINVALIDPROCTABLE:
		case WSAEDESTADDRREQ:
			errno = EINVAL;
			break;
		case WSAEINPROGRESS:
			errno = EINPROGRESS;
			break;
		case WSAEFAULT:
			errno = EFAULT;
			break;
		case WSAEISCONN:
			errno = EISCONN;
			break;
		case WSAEMSGSIZE:
			errno = EMSGSIZE;
			break;
		case WSAEAFNOSUPPORT:
			errno = EAFNOSUPPORT;
			break;
		case WSAEMFILE:
			errno = EMFILE;
			break;
		case WSAENOBUFS:
			errno = ENOBUFS;
			break;
		case WSAEPROTONOSUPPORT:
		case WSAEPROTOTYPE:
		case WSAESOCKTNOSUPPORT:
			errno = EPROTONOSUPPORT;
			break;
		case WSAECONNABORTED:
			errno = ECONNABORTED;
			break;
		case WSAECONNREFUSED:
			errno = ECONNREFUSED;
			break;
		case WSAECONNRESET:
			errno = ECONNRESET;
			break;
		case WSAEINTR:
			errno = EINTR;
			break;
		case WSAENOTSOCK:
			errno = ENOTSOCK;
			break;
		case WSAEOPNOTSUPP:
			errno = EOPNOTSUPP;
			break;
		case WSAEWOULDBLOCK:
			errno = EWOULDBLOCK;
			break;
		case WSAEACCES:
			errno = EACCES;
			break;
		case WSAEADDRINUSE:
			errno = EADDRINUSE;
			break;
		case WSAEADDRNOTAVAIL:
			errno = EADDRNOTAVAIL;
			break;
		case WSAEHOSTUNREACH:
		case WSAEHOSTDOWN:
		case WSAHOST_NOT_FOUND:
		case WSAENETDOWN:
		case WSAENETUNREACH:
		case WSAENETRESET:
			errno = EHOSTUNREACH;
			break;
		case WSAENOTCONN:
		case WSAESHUTDOWN:
		case WSAEDISCON:
			errno = ENOTCONN;
			break;
		default:
			ereport(NOTICE,
					(errmsg_internal("unrecognized win32 socket error code: %d", WSAGetLastError())));
			errno = EINVAL;
	}
}