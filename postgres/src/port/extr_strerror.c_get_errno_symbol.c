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
#define  E2BIG 186 
#define  EACCES 185 
#define  EADDRINUSE 184 
#define  EADDRNOTAVAIL 183 
#define  EAFNOSUPPORT 182 
#define  EAGAIN 181 
#define  EALREADY 180 
#define  EBADF 179 
#define  EBADMSG 178 
#define  EBUSY 177 
#define  ECHILD 176 
#define  ECONNABORTED 175 
#define  ECONNREFUSED 174 
#define  ECONNRESET 173 
#define  EDEADLK 172 
#define  EDOM 171 
#define  EEXIST 170 
#define  EFAULT 169 
#define  EFBIG 168 
#define  EHOSTUNREACH 167 
#define  EIDRM 166 
#define  EINPROGRESS 165 
#define  EINTR 164 
#define  EINVAL 163 
#define  EIO 162 
#define  EISCONN 161 
#define  EISDIR 160 
#define  ELOOP 159 
#define  EMFILE 158 
#define  EMLINK 157 
#define  EMSGSIZE 156 
#define  ENAMETOOLONG 155 
#define  ENFILE 154 
#define  ENOBUFS 153 
#define  ENODEV 152 
#define  ENOENT 151 
#define  ENOEXEC 150 
#define  ENOMEM 149 
#define  ENOSPC 148 
#define  ENOSYS 147 
#define  ENOTCONN 146 
#define  ENOTDIR 145 
#define  ENOTEMPTY 144 
#define  ENOTSOCK 143 
#define  ENOTSUP 142 
#define  ENOTTY 141 
#define  ENXIO 140 
#define  EOPNOTSUPP 139 
#define  EOVERFLOW 138 
#define  EPERM 137 
#define  EPIPE 136 
#define  EPROTONOSUPPORT 135 
#define  ERANGE 134 
#define  EROFS 133 
#define  ESRCH 132 
#define  ETIMEDOUT 131 
#define  ETXTBSY 130 
#define  EWOULDBLOCK 129 
#define  EXDEV 128 

__attribute__((used)) static char *
get_errno_symbol(int errnum)
{
	switch (errnum)
	{
		case E2BIG:
			return "E2BIG";
		case EACCES:
			return "EACCES";
#ifdef EADDRINUSE
		case EADDRINUSE:
			return "EADDRINUSE";
#endif
#ifdef EADDRNOTAVAIL
		case EADDRNOTAVAIL:
			return "EADDRNOTAVAIL";
#endif
		case EAFNOSUPPORT:
			return "EAFNOSUPPORT";
#ifdef EAGAIN
		case EAGAIN:
			return "EAGAIN";
#endif
#ifdef EALREADY
		case EALREADY:
			return "EALREADY";
#endif
		case EBADF:
			return "EBADF";
#ifdef EBADMSG
		case EBADMSG:
			return "EBADMSG";
#endif
		case EBUSY:
			return "EBUSY";
		case ECHILD:
			return "ECHILD";
#ifdef ECONNABORTED
		case ECONNABORTED:
			return "ECONNABORTED";
#endif
		case ECONNREFUSED:
			return "ECONNREFUSED";
#ifdef ECONNRESET
		case ECONNRESET:
			return "ECONNRESET";
#endif
		case EDEADLK:
			return "EDEADLK";
		case EDOM:
			return "EDOM";
		case EEXIST:
			return "EEXIST";
		case EFAULT:
			return "EFAULT";
		case EFBIG:
			return "EFBIG";
#ifdef EHOSTUNREACH
		case EHOSTUNREACH:
			return "EHOSTUNREACH";
#endif
		case EIDRM:
			return "EIDRM";
		case EINPROGRESS:
			return "EINPROGRESS";
		case EINTR:
			return "EINTR";
		case EINVAL:
			return "EINVAL";
		case EIO:
			return "EIO";
#ifdef EISCONN
		case EISCONN:
			return "EISCONN";
#endif
		case EISDIR:
			return "EISDIR";
#ifdef ELOOP
		case ELOOP:
			return "ELOOP";
#endif
		case EMFILE:
			return "EMFILE";
		case EMLINK:
			return "EMLINK";
		case EMSGSIZE:
			return "EMSGSIZE";
		case ENAMETOOLONG:
			return "ENAMETOOLONG";
		case ENFILE:
			return "ENFILE";
		case ENOBUFS:
			return "ENOBUFS";
		case ENODEV:
			return "ENODEV";
		case ENOENT:
			return "ENOENT";
		case ENOEXEC:
			return "ENOEXEC";
		case ENOMEM:
			return "ENOMEM";
		case ENOSPC:
			return "ENOSPC";
		case ENOSYS:
			return "ENOSYS";
#ifdef ENOTCONN
		case ENOTCONN:
			return "ENOTCONN";
#endif
		case ENOTDIR:
			return "ENOTDIR";
#if defined(ENOTEMPTY) && (ENOTEMPTY != EEXIST) /* same code on AIX */
		case ENOTEMPTY:
			return "ENOTEMPTY";
#endif
#ifdef ENOTSOCK
		case ENOTSOCK:
			return "ENOTSOCK";
#endif
#ifdef ENOTSUP
		case ENOTSUP:
			return "ENOTSUP";
#endif
		case ENOTTY:
			return "ENOTTY";
		case ENXIO:
			return "ENXIO";
#if defined(EOPNOTSUPP) && (!defined(ENOTSUP) || (EOPNOTSUPP != ENOTSUP))
		case EOPNOTSUPP:
			return "EOPNOTSUPP";
#endif
#ifdef EOVERFLOW
		case EOVERFLOW:
			return "EOVERFLOW";
#endif
		case EPERM:
			return "EPERM";
		case EPIPE:
			return "EPIPE";
		case EPROTONOSUPPORT:
			return "EPROTONOSUPPORT";
		case ERANGE:
			return "ERANGE";
#ifdef EROFS
		case EROFS:
			return "EROFS";
#endif
		case ESRCH:
			return "ESRCH";
#ifdef ETIMEDOUT
		case ETIMEDOUT:
			return "ETIMEDOUT";
#endif
#ifdef ETXTBSY
		case ETXTBSY:
			return "ETXTBSY";
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
		case EWOULDBLOCK:
			return "EWOULDBLOCK";
#endif
		case EXDEV:
			return "EXDEV";
	}

	return NULL;
}