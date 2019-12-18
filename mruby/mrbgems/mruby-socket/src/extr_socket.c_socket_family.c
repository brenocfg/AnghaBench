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
struct sockaddr_storage {int ss_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;

/* Variables and functions */
 int AF_UNSPEC ; 
 int getsockname (int,struct sockaddr*,int*) ; 

__attribute__((used)) static int
socket_family(int s)
{
  struct sockaddr_storage ss;
  socklen_t salen;

  salen = sizeof(ss);
  if (getsockname(s, (struct sockaddr *)&ss, &salen) == -1)
    return AF_UNSPEC;
  return ss.ss_family;
}