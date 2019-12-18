#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_6__ {int end; int p; } ;
typedef  TYPE_1__* STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  SCARD_LOCK_SEC ; 
 int SEC_ENCRYPT ; 
 int /*<<< orphan*/  g_licence_error_result ; 
 int /*<<< orphan*/  g_licence_issued ; 
 int /*<<< orphan*/  g_rc4_key_len ; 
 int /*<<< orphan*/  g_sec_sign_key ; 
 int /*<<< orphan*/  hexdump (int,int) ; 
 int /*<<< orphan*/  mcs_send_to_channel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (TYPE_1__*,int) ; 
 int /*<<< orphan*/  s_pop_layer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scard_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scard_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_encrypt (int,int) ; 
 int /*<<< orphan*/  sec_hdr ; 
 int /*<<< orphan*/  sec_sign (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void
sec_send_to_channel(STREAM s, uint32 flags, uint16 channel)
{
	int datalen;

#ifdef WITH_SCARD
	scard_lock(SCARD_LOCK_SEC);
#endif

	s_pop_layer(s, sec_hdr);
	if ((!g_licence_issued && !g_licence_error_result) || (flags & SEC_ENCRYPT))
		out_uint32_le(s, flags);

	if (flags & SEC_ENCRYPT)
	{
		flags &= ~SEC_ENCRYPT;
		datalen = s->end - s->p - 8;

#ifdef WITH_DEBUG
		DEBUG(("Sending encrypted packet:\n"));
		hexdump(s->p + 8, datalen);
#endif

		sec_sign(s->p, 8, g_sec_sign_key, g_rc4_key_len, s->p + 8, datalen);
		sec_encrypt(s->p + 8, datalen);
	}

	mcs_send_to_channel(s, channel);

#ifdef WITH_SCARD
	scard_unlock(SCARD_LOCK_SEC);
#endif
}