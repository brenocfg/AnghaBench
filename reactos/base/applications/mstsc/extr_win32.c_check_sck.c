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
typedef  int /*<<< orphan*/  tm ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PostQuitMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (struct timeval*,int) ; 
 int g_block ; 
 scalar_t__ g_tcp_sck ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 scalar_t__ ui_read_wire () ; 

__attribute__((used)) static int
check_sck(void)
{
  fd_set rfds;
  struct timeval tm;
  int count;
  int rv;

  rv = 0;
  if (g_block == 0)
  {
    g_block = 1;
    /* see if there really is data */
    FD_ZERO(&rfds);
    FD_SET((unsigned int)g_tcp_sck, &rfds);
    ZeroMemory(&tm, sizeof(tm));
    count = select(g_tcp_sck + 1, &rfds, 0, 0, &tm);
    if (count > 0)
    {
      if (ui_read_wire())
      {
        rv = 1;
      }
      else
      {
        PostQuitMessage(0);
      }
    }
    g_block = 0;
  }
  return rv;
}