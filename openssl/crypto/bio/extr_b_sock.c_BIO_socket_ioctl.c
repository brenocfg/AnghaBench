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
 char* ARG ; 
 int /*<<< orphan*/  ERR_LIB_SYS ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 int ioctlsocket (int,long,char*) ; 

int BIO_socket_ioctl(int fd, long type, void *arg)
{
    int i;

#  ifdef __DJGPP__
    i = ioctlsocket(fd, type, (char *)arg);
#  else
#   if defined(OPENSSL_SYS_VMS)
    /*-
     * 2011-02-18 SMS.
     * VMS ioctl() can't tolerate a 64-bit "void *arg", but we
     * observe that all the consumers pass in an "unsigned long *",
     * so we arrange a local copy with a short pointer, and use
     * that, instead.
     */
#    if __INITIAL_POINTER_SIZE == 64
#     define ARG arg_32p
#     pragma pointer_size save
#     pragma pointer_size 32
    unsigned long arg_32;
    unsigned long *arg_32p;
#     pragma pointer_size restore
    arg_32p = &arg_32;
    arg_32 = *((unsigned long *)arg);
#    else                       /* __INITIAL_POINTER_SIZE == 64 */
#     define ARG arg
#    endif                      /* __INITIAL_POINTER_SIZE == 64 [else] */
#   else                        /* defined(OPENSSL_SYS_VMS) */
#    define ARG arg
#   endif                       /* defined(OPENSSL_SYS_VMS) [else] */

    i = ioctlsocket(fd, type, ARG);
#  endif                        /* __DJGPP__ */
    if (i < 0)
        ERR_raise_data(ERR_LIB_SYS, get_last_socket_error(),
                       "calling ioctlsocket()");
    return i;
}