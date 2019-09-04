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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 scalar_t__ SEC_EXCHANGE_PKT ; 
 scalar_t__ SEC_PADDING_SIZE ; 
 int /*<<< orphan*/  g_sec_crypted_random ; 
 scalar_t__ g_server_public_key_len ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_init (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sec_send (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
sec_establish_key(void)
{
	uint32 length = g_server_public_key_len + SEC_PADDING_SIZE;
	uint32 flags = SEC_EXCHANGE_PKT;
	STREAM s;

	s = sec_init(flags, length + 4);

	out_uint32_le(s, length);
	out_uint8p(s, g_sec_crypted_random, g_server_public_key_len);
	out_uint8s(s, SEC_PADDING_SIZE);

	s_mark_end(s);
	sec_send(s, flags);
}