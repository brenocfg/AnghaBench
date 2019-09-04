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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  VCHANNEL ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_ENCRYPT ; 
 int /*<<< orphan*/  channel_hdr ; 
 scalar_t__ g_encryption ; 
 int /*<<< orphan*/  s_push_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_init (int /*<<< orphan*/ ,scalar_t__) ; 

STREAM
channel_init(VCHANNEL * channel, uint32 length)
{
	STREAM s;

	s = sec_init(g_encryption ? SEC_ENCRYPT : 0, length + 8);
	s_push_layer(s, channel_hdr, 8);
	return s;
}