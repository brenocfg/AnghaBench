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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  to_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  m_spi_no ; 
 int platform_spi_send_recv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ timed_out (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdcard_wait_not_busy( uint32_t us )
{
  to_t to;

  set_timeout( &to, us );
  while (platform_spi_send_recv( m_spi_no, 8, 0xff ) != 0xff) {
    if (timed_out( &to )) {
      goto fail;
    }
  }
  return TRUE;

  fail:
  return FALSE;
}