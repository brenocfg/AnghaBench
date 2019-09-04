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
struct pbuf {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  pbuf_free_int ; 
 int /*<<< orphan*/  tcpip_callback_with_block (int /*<<< orphan*/ ,struct pbuf*,int /*<<< orphan*/ ) ; 

err_t
pbuf_free_callback(struct pbuf *p)
{
  return tcpip_callback_with_block(pbuf_free_int, p, 0);
}