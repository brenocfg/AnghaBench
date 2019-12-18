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
struct key_type {int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct key_type const*) ; 
 int /*<<< orphan*/  M_FATAL ; 
 scalar_t__ cipher_kt_mode_aead (int /*<<< orphan*/ ) ; 
 scalar_t__ cipher_kt_mode_ofb_cfb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 

void
check_replay_consistency(const struct key_type *kt, bool packet_id)
{
    ASSERT(kt);

    if (!packet_id && (cipher_kt_mode_ofb_cfb(kt->cipher)
                       || cipher_kt_mode_aead(kt->cipher)))
    {
        msg(M_FATAL, "--no-replay cannot be used with a CFB, OFB or AEAD mode cipher");
    }
}