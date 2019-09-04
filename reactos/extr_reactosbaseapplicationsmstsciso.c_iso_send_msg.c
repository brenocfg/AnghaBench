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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_init (int) ; 
 int /*<<< orphan*/  tcp_send (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iso_send_msg(uint8 code)
{
	STREAM s;

	s = tcp_init(11);

	out_uint8(s, 3);	/* version */
	out_uint8(s, 0);	/* reserved */
	out_uint16_be(s, 11);	/* length */

	out_uint8(s, 6);	/* hdrlen */
	out_uint8(s, code);
	out_uint16(s, 0);	/* dst_ref */
	out_uint16(s, 0);	/* src_ref */
	out_uint8(s, 0);	/* class */

	s_mark_end(s);
	tcp_send(s);
}