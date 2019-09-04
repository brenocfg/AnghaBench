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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  j ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int get_last_socket_error () ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*) ; 

int BIO_sock_error(int sock)
{
    int j = 0, i;
    socklen_t size = sizeof(j);

    /*
     * Note: under Windows the third parameter is of type (char *) whereas
     * under other systems it is (void *) if you don't have a cast it will
     * choke the compiler: if you do have a cast then you can either go for
     * (char *) or (void *).
     */
    i = getsockopt(sock, SOL_SOCKET, SO_ERROR, (void *)&j, &size);
    if (i < 0)
        return get_last_socket_error();
    else
        return j;
}